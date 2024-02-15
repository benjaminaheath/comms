#include "phy.h"

Physical* create_phy(){
    Physical* phy = (Physical*) malloc(sizeof(Physical));
    phy->chan_send = 0;
    phy->chan_recv = 0;
    return phy;
}

void destroy_phy(Physical* phy){
    free(phy);
}

void send_phy(Physical* phy, uint8_t byte){
    phy->chan_send = byte;
}

uint8_t recv_phy(Physical* phy){
    phy->chan_recv = __channel(phy);

}

void print_phy(Physical* phy){
    print_byte(phy->chan_send);
    print_byte(phy->chan_recv);
}

static uint8_t __channel(Physical* phy){
    #ifdef PHY_CLEAR_CHANNEL
    return phy->chan_send;
    #elif defined(PHY_NOISY_CHANNEL)
    return __noise(phy->chan_send);
    #endif
}

static uint8_t __noise(uint8_t byte){
    // flip a random bit if this is a noisy frame
    if(rand() % PHY_NOISE_FREQ){
        uint8_t mask = 1 << rand() % 8; // create a mask to flip a single bit
        return byte ^ mask;
    }
    return byte;
}
