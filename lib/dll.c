#include "dll.h"

void create_dll(DLL* dll){
    dll->buf = (uint8_t*) malloc(DLL_BUF_MAX * sizeof(uint8_t));
    dll->buf_size = DLL_BUF_MAX;
    dll->buf_end = 0;
    dll->mode = WAIT;
}

void destroy_dll(DLL* dll){
    free(dll->buf);
    free(dll);
}

void send_dll(NET_packet pkt){
    /* 
        Take contents of net pkt to build frame
        Call send_phy to transmit over physical layer
    */
    
    // packet fragmentation
    uint8_t num_frames = __get_num_pkt_fragments(pkt.pkt_size,DLL_PAYLOAD_MAX);
    uint8_t* len_payloads = __get_len_pkt_fragments(pkt.pkt_size,DLL_PAYLOAD_MAX);
    uint8_t** fragments = __get_pkt_fragments(len_payloads,num_frames,pkt.packet,pkt.pkt_size);

    for(int f = 0; f < num_frames; ++f){
        uint8_t* frame = NULL;
        size_t frame_len = 0;
        // append header byte
        append_byte(&frame,&frame_len,DLL_HEAD_BYTE);

        // generate control subframe
        uint16_t ctrl = __get_control_subframe(f,(f == num_frames-1),MSG,0xC3);
        uint8_t ctrl_high_byte = ctrl >> 8;
        uint8_t ctrl_low_byte = ctrl;
        append_byte(&frame,&frame_len,ctrl_high_byte);
        append_byte(&frame,&frame_len,ctrl_low_byte);

        // generate addressing subframe
        uint8_t src_byte = 0x00;
        uint8_t dst_byte = 0xFF;
        append_byte(&frame,&frame_len,src_byte);
        append_byte(&frame,&frame_len,dst_byte);

        // generate length subframe
        append_byte(&frame,&frame_len,len_payloads[f]);

        // append payload
        append_bytes(&frame,&frame_len,fragments[f],len_payloads[f]);

        // generate checksum
        uint16_t checksum = __get_checksum_subframe(frame,frame_len); 
        uint8_t checksum_high_byte = checksum >> 8;
        uint8_t checksum_low_byte = checksum;
        append_byte(&frame,&frame_len,checksum_high_byte);
        append_byte(&frame,&frame_len,checksum_low_byte);

        // escaping for packet
        

        // append footer byte
        append_byte(&frame,&frame_len,DLL_FOOT_BYTE);

        // hand frame to PHY for transmission
        print_bytes(frame,frame_len);
    }
}

recv_callback_dll link_dll(DLL* dll){
    return recv_dll;
}

NET_packet recv_dll(){

}

// DLL service loop that polls PHY to check for received bytes
void service_dll(Physical* phy, DLL* dll){ 
    /* 
        Store bytes in a simple buffer, and if full, flush the buffer
    */
    if(phy->byte_recv){ 
        // write to next address in buffer
        uint8_t byte = dll->recv_phy(phy);
        if(dll->mode == WAIT){ // buffer in WAIT mode for head byte
            if(byte == DLL_HEAD_BYTE){
                dll->mode == LISTEN;
                __buf_write(dll,byte);
            }
            else{
                return;
            }
        }
        else if(dll->mode == LISTEN){ // buffer in LISTEN mode storing bytes
            if(byte == DLL_FOOT_BYTE){
                dll->mode == ESCAPE;
            }
            __buf_write(dll,byte);
        }
        else if(dll->mode == ESCAPE){ // buffer in ESCAPE mode checking for escape or end
            if(byte == DLL_FOOT_BYTE){ // just escaping
                __buf_write(dll,byte); 
            }
            else{ // actual end of frame if non-escape
                dll->mode == WAIT; 
                return;
            }
        }
    }
}

// INTERNAL METHODS
// DLL receive buffer methods
static void __buf_write(DLL* dll, uint8_t byte){
    dll->buf[dll->buf_end] = byte; // write byte to end pointer
    dll->buf_end++;
}

static uint8_t __buf_read(DLL* dll, unsigned int index){
    return dll->buf[index];
}

static void __buf_flush(DLL* dll){
    for(int b = 0; b < dll->buf_size; ++b){
        dll->buf[b] = 0; // zero out all bytes in buffer
    }
}

// Packet fragmentation methods
static uint8_t __get_num_pkt_fragments(uint8_t pkt_length, uint8_t max_length){
    if(pkt_length == 0){return 1;}

    uint8_t full_pkts = pkt_length / max_length; // number of full packets
    uint8_t frag_pkt_len = pkt_length % max_length; // length of final packet

    uint8_t num_frames = full_pkts; // number of frames is at least full packets
    if(frag_pkt_len > 0) {num_frames++;} // if short packet fragment, add it

    return num_frames;
}

static uint8_t* __get_len_pkt_fragments(uint8_t pkt_length, uint8_t max_length){
    uint8_t num_frames = __get_num_pkt_fragments(pkt_length, max_length);
    uint8_t* frag_lengths = (uint8_t*) malloc(num_frames*sizeof(uint8_t));
    if(frag_lengths != NULL){
        if(num_frames > 1){
            for(int p = 0; p < num_frames; ++p){
                if(p < num_frames - 1){frag_lengths[p] = max_length;} //
                else{
                    if(pkt_length % max_length == 0){frag_lengths[p] = max_length;}
                    else{frag_lengths[p] = pkt_length % max_length;}
                }
            }
        } else { // 1 frame packet length
            // covers edge case of dummy payload: 1 frame, 0 payload
            frag_lengths[0] = pkt_length;
        }
    } else {
        fprintf(stderr,"__get_len_pkt_fragments failed");
        exit(EXIT_FAILURE);
    }

    return frag_lengths;
}

static uint8_t** __get_pkt_fragments(uint8_t* len_fragments, uint8_t num_fragments, uint8_t* pkt, size_t len_pkt){
    uint8_t** fragments = (uint8_t**) malloc(num_fragments*sizeof(uint8_t*));
    if(fragments != NULL){
        size_t start_index = 0;
        for(size_t f = 0; f < num_fragments; ++f){
               size_t len_fragment = len_fragments[f]; 
               fragments[f] = get_bytes_from(pkt,len_pkt,start_index,len_fragment);
               start_index += len_fragment;
        }
    } else {
        fprintf(stderr,"__get_pkt_fragments failed");
        exit(EXIT_FAILURE);
    }
    return fragments;
}

static uint16_t __get_control_subframe(uint8_t fragment, bool final, frm_type_t type, uint8_t seq_num){
    uint16_t ctrl = 0;
    if(!final){ctrl |= fragment & 0x7;}
    else{ctrl |= 0x7;}

    uint8_t protocol = 0; 
    switch(DLL_PROTOCOL){
        case 0: protocol = 0x0; break;
        case 1: protocol = 0x3; break;
        default: protocol = 0x0;
    }
    ctrl |= protocol << 3;
    ctrl |= type << 5;
    ctrl |= DLL_CHECKSUM << 7;
    ctrl |= seq_num << 8;
}

static uint16_t __get_checksum_subframe(uint8_t* frame, size_t frame_len){
    switch(DLL_CHECKSUM){
        case 0: return __get_parity(frame, frame_len);
        case 1: return __get_CRC16(frame,frame_len);
    }
}

static uint16_t __get_CRC16(uint8_t* frame, size_t frame_len){
    uint16_t crc = 0xFFFF; // Initial value
    size_t i, j;

    for (i = 0; i < frame_len; ++i) {
        crc ^= (uint16_t)frame[i];
        for (j = 0; j < 8; ++j) {
            if (crc & 0x0001) {
                crc = (crc >> 1) ^ DLL_CRC16_POLYNOMIAL;
            } else {
                crc >>= 1;
            }
        }
    }
    return crc;
    
}

static uint16_t __get_parity(uint8_t* fame, size_t frame_len){
    return (uint16_t) 0xC3C3;
}