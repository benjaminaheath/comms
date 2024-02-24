#include "main.h"

int main() {
    // set up physical instance and link callback
    printf("STARTING SIMULATION\n");
    uint8_t* ptr = NULL;
    size_t len_ptr = 0;
    append_byte(&ptr,&len_ptr,0xFF);
    print_ptr(ptr);
    print_bytes(ptr, len_ptr);

    uint8_t* new_ptr = NULL;
    size_t len_new_ptr = 0;
    append_byte(&new_ptr, &len_new_ptr, 0xAA);
    print_ptr(new_ptr);
    print_bytes(new_ptr, len_new_ptr);

    append_bytes(&ptr, &len_ptr, new_ptr, len_new_ptr);
    print_ptr(ptr);
    print_bytes(ptr,len_ptr);
    // dll_send_case();
    // dll_receive_case();
    printf("%u ",get_byte(ptr,len_new_ptr,0));
    printf("%u ",get_byte(ptr,len_new_ptr,1));
    printf("%u ",get_byte(ptr,len_new_ptr,3));


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