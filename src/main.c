#include "main.h"

int main() {
    // set up physical instance and link callback
    printf("STARTING SIMULATION\n");
    dll_send_case();
    dll_receive_case();
    printf("ENDING SIMULATION\n");
    return 0;
}

void dll_send_case(){
    printf("Start DLL Send Case\n");

    printf("End DLL Send Case\n");
}

void dll_receive_case(){
    printf("Start DLL Receive Case\n");

    printf("End DLL Receive Case\n");
}