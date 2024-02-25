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

void print_ptr(void* ptr){
    printf("ptr:%p\n", ptr);
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

void append_byte(uint8_t** bytes, size_t* num_bytes, uint8_t byte){
    *bytes  = (uint8_t*) realloc(*bytes,(*num_bytes + 1) * sizeof(uint8_t));
    if(*bytes != NULL){ // allocation success
        (*bytes)[*num_bytes] = byte;
        ++(*num_bytes);
    } else { // error reallocating
        fprintf(stderr,"append_byte Failed\n");
        exit(EXIT_FAILURE);
    }
}

void append_bytes(uint8_t** bytes, size_t* num_bytes, uint8_t* new_bytes, size_t num_new_bytes){
    *bytes = (uint8_t*) realloc(*bytes, (*num_bytes + num_new_bytes) * sizeof(uint8_t));
    if(*bytes != NULL){ // allocation success
        for(size_t b = 0; b < num_new_bytes; ++b){
            (*bytes)[*num_bytes + b] = new_bytes[b];
        }
        *num_bytes += num_new_bytes;
    } else {
        fprintf(stderr,"append_bytes Failed\n");
        exit(EXIT_FAILURE);
    }

}

void insert_byte(uint8_t** bytes, size_t* num_bytes, uint8_t byte, size_t insert_index){
    *bytes = (uint8_t*) realloc(*bytes, (*num_bytes + 1) * sizeof(uint8_t));
    if(*bytes != NULL){
        //shuffle bytes after insert by 1 - start from end
        for(size_t b = *num_bytes; b > insert_index; --b){
            (*bytes)[b+1] = (*bytes)[b];
        }
        //insert byte
        (*bytes)[insert_index] = byte;
        //increment length
        ++(*num_bytes);

    } else {
        fprintf(stderr,"insert_byte failed\n");
        exit(EXIT_FAILURE);
    }
}

uint8_t get_byte(uint8_t* bytes, size_t num_bytes, size_t index){
    if(index <= num_bytes){return bytes[index];}
    else{
        fprintf(stderr,"get_byte out of range\n");
        exit(EXIT_FAILURE);
    }
}


uint8_t* get_bytes_from(uint8_t* bytes, size_t num_bytes, size_t index_start, size_t num_in_range){
    size_t index_end = index_start + num_in_range;
    if(num_in_range == 0){
        fprintf(stderr,"get_bytes_from zero range\n");
        exit(EXIT_FAILURE);
    }
    if(index_end <= num_bytes){
        uint8_t* bytes_from = __get_bytes(bytes,index_start,index_end);
    } else {
        fprintf(stderr,"get_bytes_from out of range\n");
        exit(EXIT_FAILURE);
    }
}
uint8_t* get_bytes_range(uint8_t* bytes, size_t num_bytes, size_t index_start, size_t index_end){
    if(index_end <= num_bytes && index_start <= index_end){
        uint8_t* bytes_range = __get_bytes(bytes,index_start,index_end);
    } else {
        fprintf(stderr,"get_bytes_range out of range\n");
        exit(EXIT_FAILURE);
    }
}

static uint8_t* __get_bytes(uint8_t* bytes, size_t index_start, size_t index_end){
    uint8_t* bytes_in_range = (uint8_t*) malloc((index_end - index_start)*sizeof(uint8_t));
    if(bytes_in_range != NULL){
        for(size_t b = index_start; b <= index_end; ++b){
            bytes_in_range[b-index_start] = bytes[b];
        }
    } else {
        fprintf(stderr,"__get_bytes failed\n");
        exit(EXIT_FAILURE);
    }
    return bytes_in_range;
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