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
    size_t num_byte = 20;
    uint8_t* bytes = rand_bytes(num_byte); 

    NET_packet pkt = {bytes, num_byte};
    printf("NET Packet SEND:\n");
    print_bytes(pkt.packet,pkt.pkt_size);
    printf("\n");
    send_dll(pkt);
    printf("End DLL Send Case\n");
}