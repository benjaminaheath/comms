#include "dll.h"

void create_dll(DLL* dll){
    dll->buf = (uint8_t*) malloc(DLL_BUF_MAX * sizeof(uint8_t));
    dll->buf_size = DLL_BUF_MAX;
    dll->buf_end = 0;
    dll->buf_mode = WAIT;
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
        if(dll->buf_mode == WAIT){ // buffer in WAIT mode for head byte
            if(byte == DLL_HEAD_BYTE){
                dll->buf_mode == LISTEN;
                __buf_write(dll,byte);
            }
            else{
                return;
            }
        }
        else if(dll->buf_mode == LISTEN){ // buffer in LISTEN mode storing bytes
            if(byte == DLL_FOOT_BYTE){
                dll->buf_mode == ESCAPE;
            }
            __buf_write(dll,byte);
        }
        else if(dll->buf_mode == ESCAPE){ // buffer in ESCAPE mode checking for escape or end
            if(byte == DLL_FOOT_BYTE){ // just escaping
                __buf_write(dll,byte); 
            }
            else{ // actual end of frame if non-escape
                dll->buf_mode == WAIT; 
                return;
            }
        }
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