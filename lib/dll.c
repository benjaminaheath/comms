#include "dll.h"

void create_dll(DLL* dll){
    dll->frame_buf_size = 0;
    dll->frame_buf = NULL;
}

void destroy_dll(DLL* dll){
    free(dll->frame_buf);
    free(dll);
}

recv_callback_dll link_dll(DLL* dll){
    return recv_dll;
}

NET_packet recv_dll(){

}

// DLL service loop that polls PHY to check for received bytes
void service_dll(DLL* dll){ 
    /* 
    check if phy has raised byte_recv flag
    if so, queue new byte into dll frame buf
    and if buffer has been updated, check if a valid DLL frame is there
    */
    if(dll->recv_phy() != NULL){ // placeholder
        if(dll->frame_buf_size <= DLL_BUF_MAX){ // queue byte in buffer

        }
        else{ // if no space, shift out oldest byte in buffer

        }
    }
    else{
        // memory leak condition
    }
    // review the new dll byte buffer for a valid frame
}