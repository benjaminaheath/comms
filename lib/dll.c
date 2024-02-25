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

        // generate control subframe

        // generate addressing subframe

        // generate length subframe
        uint8_t payload_length = len_payloads[f];
        append_byte(&frame,&frame_len,payload_length);

        // append payload
        // append_bytes(&frame,&frame_len,)
        // generate checksum

        // escaping for packet

        // wrap in header and footer

        // build frame struct
        
        // hand frame to PHY for transmission
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
