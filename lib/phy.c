#include "phy.h"

static const uint32_t noise = (unsigned) (PHY_NOISE_FREQ * RAND_MAX);

recv_callback_phy phy_phy(){
    return recv_phy;
}

void send_phy(uint8_t byte, recv_callback_phy recv){
    recv(__channel(byte));
}

void recv_phy(uint8_t byte){
    recv_callback_dll dll_recv = link_dll();
    dll_recv(byte);
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
