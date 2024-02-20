#include "dll.h"

void create_dll(DLL* dll){
    dll->buf = (uint8_t*) malloc(DLL_BUF_MAX * sizeof(uint8_t));
    dll->buf_size = DLL_BUF_MAX;
    dll->buf_end = 0;
}

void destroy_dll(DLL* dll){
    free(dll->buf);
    free(dll);
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
        uint8_t byte = dll->recv_phy();
        __buf_write(dll,byte);
        // review the new dll byte buffer for a valid frame
        for(int b = 0; b < dll->buf_end; ++b){
            /*
                Clear buffer of escaped bytes
                Scan for header byte
                If present, scan for footer byte
            */
        }
        // if full and no valid frame, flush buffer 
    }
}

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