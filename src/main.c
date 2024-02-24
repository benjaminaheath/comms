#include "main.h"

int main() {
    // set up physical instance and link callback
    printf("STARTING SIMULATION\n");
    uint8_t* ptr = NULL;
    size_t len_ptr = 0;
    append_byte(&ptr,&len_ptr,0x0);
    append_byte(&ptr,&len_ptr,0x1);
    append_byte(&ptr,&len_ptr,0x2);
    append_byte(&ptr,&len_ptr,0x3);
    append_byte(&ptr,&len_ptr,0x4);


    print_bytes(ptr,len_ptr);
    uint8_t* bytes_from = get_bytes_from(ptr,len_ptr,1,1); // index 0, 3 total (0-2)
    uint8_t* bytes_range = get_bytes_range(ptr,len_ptr,1,3); // index 1 to 3 
    print_bytes(bytes_from,1);
    print_bytes(bytes_range,3);
    printf("ENDING SIMULATION\n");
    return 0;
}

void dll_send_case(){
    printf("Start DLL Send Case\n");
    /*
        Generate bytes and fill out NET packet
        call send_dll to send
    */
    uint8_t* bytes = rand_bytes(46); // generate 10 bytes
    NET_packet pkt = {bytes, 46};
    send_dll(pkt);
    printf("End DLL Send Case\n");
}

void dll_receive_case(){
    printf("Start DLL Receive Case\n");

    printf("End DLL Receive Case\n");
}