#include "dll.h"

static DLL dll;

void send_dll(NET_packet pkt){
    /* 
        Take contents of net pkt to build frame
        Call send_phy to transmit over physical layer
    */
    // prepare phy for transmission and receive 
    recv_callback_phy recv = phy_phy();

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
        __escape_frame(&frame,&frame_len);        

        // append footer byte
        append_byte(&frame,&frame_len,DLL_FOOT_BYTE);

        // hand frame to PHY for transmission
        for(size_t f = 0; f < frame_len; ++f){
            send_phy(frame[f], recv);
        }
        printf("\n");
    }
}

recv_callback_dll link_dll(){
    dll.DEV_ADDR = DLL_MAC_RECV;
    dll.buf = NULL;
    dll.buf_size = 0;
    dll.frmbuf = NULL;
    dll.frmbuf_size = 0;
    dll.mode = WAIT;
    return recv_dll;
}

void recv_dll(uint8_t byte){
    enum buf_mode next_mode;
    // print_byte(byte);
    printf(" : ");
    switch (dll.mode)
    {
    case WAIT:
        // printf("Wait State");
        if(byte == 0x7E){next_mode = LISTEN;}
        else{next_mode = WAIT;}
        break;
    case LISTEN: 
        // printf("Listen State");
        if(byte == 0x7D){next_mode = ESCAPE;}
        else if(byte == 0x7E){next_mode = WAIT;}
        else{next_mode = LISTEN;}
        break;
    case ESCAPE:
        // printf("Escape State");
        next_mode = LISTEN;
        break;
    }
    dll.mode = next_mode;
    // printf("\n");
}

static void __recv_frame(){
    // copy frame out of buffer
    DLL_frame* frm = (DLL_frame*) malloc(sizeof(DLL_frame));
    frm->frame = get_bytes_from(dll.buf,dll.buf_size,0,dll.buf_size);
    frm->frame_len = dll.buf_size;
    // clear buffer
    free(dll.buf);
    dll.buf_size = 0;

    // helper vars for indexes
    frm->CTRL_HIGH = 0;
    frm->CTRL_LOW  = 1;
    frm->ADDR_SEND = 2;
    frm->ADDR_RECV = 3;
    frm->LENGTH    = 4; 
    frm->PAYLOAD   = 5;
    frm->CHECKSUM_HIGH = frm->frame_len - 2;
    frm->CHECKSUM_LOW  = frm->frame_len - 1;

    // validate the checksum to check if it's valid
    uint8_t  CHECKSUM_HIGH_BYTE = get_byte(frm->frame,frm->frame_len,frm->CHECKSUM_HIGH);
    uint8_t  CHECKSUM_LOW_BYTE  = get_byte(frm->frame,frm->frame_len,frm->CHECKSUM_LOW);
    uint16_t CHECKSUM           = CHECKSUM_HIGH_BYTE << 8 | CHECKSUM_LOW_BYTE;

    uint16_t CRC16 = __get_checksum_subframe(frm->frame,frm->frame_len);

    if(CRC16 != CHECKSUM){ // invalid checksum, flush
        free(frm->frame);
        free(frm);
        return;
    }

    // get control, addressing, length data
    uint8_t CTRL_HIGH_BYTE = get_byte(frm->frame,frm->frame_len,frm->CTRL_HIGH);
    uint8_t CTRL_LOW_BYTE  = get_byte(frm->frame,frm->frame_len,frm->CTRL_LOW);
    uint8_t ADDR_SEND_BYTE = get_byte(frm->frame,frm->frame_len,frm->ADDR_SEND);
    uint8_t ADDR_RECV_BYTE = get_byte(frm->frame,frm->frame_len,frm->ADDR_RECV);
    uint8_t LENGTH_BYTE    = get_byte(frm->frame,frm->frame_len,frm->LENGTH);

    if(ADDR_RECV_BYTE != DLL_MAC_RECV){ // not correct receiver, flush
        free(frm->frame);
        free(frm);
        return;
    }

    // TODO: lock in a sender once a frame is already in the buffer

    // extract control data
    uint8_t    FRAGMENT = 0x7  & CTRL_HIGH_BYTE;
    bool       FINAL    = 0x8  & CTRL_HIGH_BYTE >> 3;
    bool       PROTOCOL = 0x18 & CTRL_HIGH_BYTE >> 4;
    frm_type_t MSG_TYPE = 0x60 & CTRL_HIGH_BYTE >> 5;
    bool       CHECKTYP = 0x80 & CTRL_HIGH_BYTE >> 7;
    uint8_t    SEQ_NUM  = 0xFF & CTRL_LOW_BYTE;

    // with this information, decide what to do
    switch(MSG_TYPE){
        case MSG:
            // if message, store at end of fragment buffer
            __store_fragment(frm, FRAGMENT, SEQ_NUM);

            // if final frame present, check for a complete packet

            // if returns non-null, use returned vector to reconstruct NET pkt

            break;
        // case ACK:
            // move sliding window
            // break;
        // case NACK:
            // queue packet resend
            // break;
    }
}

// TODO: check if sequence numbers match in with others before inserting or discard
// TODO: lock in a sender once one frame is in an discard others
//       -- only allow frames to enter which have lower sequence numbers and lower fragments
//       -- or, higher sequence numbers and higher fragments
static void __store_fragment(DLL_frame* frm, uint8_t fragment, uint8_t seq, bool final){
    // TODO: Check for sequence number before performing any append

    // increase size of frame buffer
    ++dll.frmbuf_size;
    dll.frmbuf = (DLL_frame**) realloc(dll.frmbuf,dll.frmbuf_size * sizeof(DLL_frame*));

    if(fragment == 0x0) { // check if first frame is stored
        dll.first_present = true;
    }

    if(final){ // if final fragment, always store at end
        dll.frmbuf[dll.frmbuf_size - 1] = *frm;
        dll.final_present = true;
    } else { // otherwise iterate through and store pointer in order
        uint8_t frag_insert_index = 0;
        for(size_t f = 0; f < dll.frmbuf_size; ++f){
            DLL_frame frm = dll.frmbuf[f]; 
            uint8_t buf_fragment = frm.frame[frm.CTRL_HIGH] & 0x7; 
            // find buffered fragment with higher fragment number than this
            if(buf_fragment > fragment){
                frag_insert_index = f;
                break;
            }
        }
        // now, work backwards and shuffle pointers to make room for insert
        for(size_t f = dll.frmbuf_size; f <= frag_insert_index; --f){
            dll.frmbuf[f] = dll.frmbuf[f-1];
        }
        dll.frmbuf[frag_insert_index] = *frm;
    }

    // if first and final present, set fragment count total for check
}

// if we know there's a first and a final, all we need check is the length of the buffer
static bool __check_complete_pkt(){
    // given that there is a first and a final frame, check for all fragments in sequence
    size_t total = 0;
    for(size_t f = 0; f < dll.frmbuf_size - 1; ++f){
        // get current and next frames
        DLL_frame cur_frm = dll.frmbuf[f];
        DLL_frame nxt_frm = dll.frmbuf[f+1];
        // get fragment numbers
        uint8_t cur_frag = cur_frm.frame[cur_frm.CTRL_HIGH] & 0x7;
        uint8_t nxt_frag = nxt_frm.frame[nxt_frm.CTRL_HIGH] & 0x7;

        if(nxt_frag != cur_frag + 1){ // frame fragments are non-sequential
            return false;
        }
    }
    return true;
}

static NET_packet __reconstruct_pkt(){
    // iterate through the buffer
    // on each frame, take the frame length as the length needed to append bytes to the existing NET_packet buffer.
    NET_packet pkt;
    pkt.packet = NULL;
    pkt.pkt_size = 0;
    for(size_t f = 0; f < pkt.pkt_size; ++f){
        DLL_frame frm = dll.frmbuf[f];
        append_bytes(&pkt.packet,&pkt.pkt_size,frm.frame,frm.frame_len);
    }
    return pkt;
}

void service_dll(){

}


// INTERNAL METHODS
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
    // modify from spec: 3-bit fragment, next bit 
    ctrl |= fragment & 0x7;
    ctrl |= final << 3;
    ctrl |= DLL_PROTOCOL << 4;
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

static uint16_t __get_parity(uint8_t* frame, size_t frame_len){
    return (uint16_t) 0xC3C3;
}

static void __escape_frame(uint8_t** frame, size_t* frame_len){
    // look through all bytes in frame, checking for unintentional flag/escapes
    uint8_t byte;
    for(size_t b = 1; b < (*frame_len); ++b){ // skip over header; no ESC needed
        byte = (*frame)[b];

        // if flag (0x7E), prepend ESC (0x7D). if ESC (0x7D), prepend ESC (0x7D)
        if(byte == 0x7E || byte == 0x7D){
            insert_byte(frame,frame_len,DLL_ESC_BYTE,b);
            ++b; // skip over new prepended ESC
        }
    }
}