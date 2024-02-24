#include "util.h"

void print_bytes(uint8_t* bytes, size_t num_bytes){
    for(size_t b = 0; b < num_bytes; ++b){ 
        __print(bytes[b]);
    }
    printf("\n");
}

void print_byte(uint8_t byte){
    __print(byte);
}

uint8_t* rand_bytes(size_t num_bytes){
    uint8_t* bytes_ptr = (uint8_t*) malloc(num_bytes * sizeof(uint8_t));
    for(size_t b = 0; b < num_bytes; ++b){
        bytes_ptr[b] = rand_byte();
    }
    return bytes_ptr;
}

uint8_t rand_byte(){
    return rand() % 0xFF;
}

static void __print(uint8_t byte){
    #ifdef PRINT_BIN
        for(int i = 7; i >= 0; --i){
            printf("%d", (byte >> i) & 1);
        }
    #elif defined(PRINT_HEX)
        printf("0x%02X",byte);
    #elif defined(PRINT_DEC)
        printf("%u",byte);
    #endif
    printf(" ");
}