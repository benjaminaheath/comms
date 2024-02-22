#include "main.h"

int main() {
    // set up physical instance and link callback
    size_t b = 5;
    for(int i = 1; i <= b; ++i){
        uint8_t* rand = rand_bytes(i);
        // print_bytes(rand, i);
        printf("\n");
    }
    return 0;
}