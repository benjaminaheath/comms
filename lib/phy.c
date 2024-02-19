#include "phy.h"

recv_callback_phy phy_phy(Physical* phy){
    printf("Initialise phy call\n");
    return recv_phy;
}

void send_phy(Physical* phy, DLL_frame dll_frame){
    printf("phy send call\n");
    __send_phy_byte(phy,dll_frame.frame);
}

uint8_t recv_phy(Physical* phy){
    return phy->chan_recv;
}

void print_phy(Physical* phy){
    print_byte(phy->chan_recv);
    printf(" \n");
}

Physical* create_phy(){
    Physical* phy = (Physical*) malloc(sizeof(Physical));
    phy->chan_recv = 0;
    #ifdef PHY_CLEAR_CHANNEL
        phy->noise = 0;    
    #elif defined(PHY_NOISY_CHANNEL)
        phy->noise = (unsigned) (PHY_NOISE_FREQ * RAND_MAX);
    #endif
    
    return phy;
}

void destroy_phy(Physical* phy){
    free(phy);
}

static void __send_phy_byte(Physical* phy, uint8_t byte){
    phy->chan_recv = __channel(phy,byte);
}

static uint8_t __channel(Physical* phy, uint8_t byte){
    #ifdef PHY_CLEAR_CHANNEL
        return byte;
    #elif defined(PHY_NOISY_CHANNEL)
        return __noise(phy, byte);
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
