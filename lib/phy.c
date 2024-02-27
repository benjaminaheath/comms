#include "phy.h"

recv_callback_phy phy_phy(){
    return recv_phy;
}

void send_phy(uint8_t byte){
    __send_phy_byte(byte);
}

uint8_t recv_phy(){
    // take oldest byte from channel queue; remove and return it
    uint8_t byte = get_byte(&chan,&chan_size,0);
    remove_byte(&chan,&chan_size,0);
    return byte;
}

static void __send_phy_byte(uint8_t byte){
    // pass through channel (noise)
    uint8_t chan_byte = __channel(byte);
    // append byte to end of channel queue
    append_byte(&chan,&chan_size,chan_byte); 
    ++chan_size;
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
