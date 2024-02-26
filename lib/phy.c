#include "phy.h"

recv_callback_phy phy_phy(){
    return recv_phy;
}

void send_phy(uint8_t byte){
    __send_phy_byte(byte);
}

uint8_t recv_phy(){
    return chan;
}

static void __send_phy_byte(uint8_t byte){
    chan = __channel(byte);
}

static uint8_t __channel(uint8_t byte){
    #ifdef PHY_CLEAR_CHANNEL
        return byte;
    #elif defined(PHY_NOISY_CHANNEL)
        return __noise(byte);
    #endif
}

static uint8_t __noise(uint8_t byte){
    // flip a random bit if this is a noisy bit
    uint8_t mask = 0x00;
    for(int b = 0; b < 8; ++b){
        if(rand() < noise) {

            mask |= 1 << b; // create mask to XOR (flip) bit b
        }
    }
    return byte ^ mask;
}
