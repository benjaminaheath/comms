#include "phy.h"

void send_phy(Physical* phy, DLL_frame dll_frame){

}

recv_callback_phy phy_phy(Physical* phy){

}

void print_phy(Physical* phy){
    print_byte(phy->chan_send);
    print_byte(phy->chan_recv);
    printf(" \n");
}

static Physical* __create_phy(){
    Physical* phy = (Physical*) malloc(sizeof(Physical));
    phy->chan_send = 0;
    phy->chan_recv = 0;
    phy->noise = (unsigned) (PHY_NOISE_FREQ * RAND_MAX);
    return phy;
}

static void __destroy_phy(Physical* phy){
    free(phy);
}

static void __send_phy_byte(Physical* phy, uint8_t byte){
    phy->chan_send = byte;
}

static uint8_t __recv_phy_byte(Physical* phy){
    phy->chan_recv = __channel(phy);
}


static uint8_t __channel(Physical* phy){
    #ifdef PHY_CLEAR_CHANNEL
        return phy->chan_send;
    #elif defined(PHY_NOISY_CHANNEL)
        return __noise(phy, phy->chan_send);
    #endif
}

static uint8_t __noise(Physical* phy, uint8_t byte){
    // flip a random bit if this is a noisy bit
    uint8_t mask = 0x00;
    for(int b = 0; b < 8; ++b){
        if(rand() < phy->noise) {

            mask |= 1 << b; // create mask to XOR (flip) bit b
        }
    }
    return byte ^ mask;
}
