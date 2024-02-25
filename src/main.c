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
    uint8_t* bytes = rand_bytes(30); // generate 10 bytes
    NET_packet pkt = {bytes, 30};
    send_dll(pkt);
    printf("End DLL Send Case\n");
}

void dll_receive_case(){
    printf("Start DLL Receive Case\n");

    printf("End DLL Receive Case\n");
}