#include "main.h"

int main() {
    // set up physical instance and link callback
    printf("STARTING SIMULATION\n");
    dll_send_case();
    printf("ENDING SIMULATION\n");
    return 0;
}

void dll_send_case(){
    printf("Start DLL Send Case\n");
    /*
        Generate bytes and fill out NET packet
        call send_dll to send
    */
    size_t num_byte = 30;
    uint8_t* bytes = rand_bytes(num_byte); 
    append_byte(&bytes,&num_byte,0x7E);
    append_byte(&bytes,&num_byte,0x7D);

    NET_packet pkt = {bytes, num_byte};
    send_dll(pkt);
    printf("End DLL Send Case\n");
}

void dll_receive_case(){
    printf("Start DLL Receive Case\n");

    printf("End DLL Receive Case\n");
}