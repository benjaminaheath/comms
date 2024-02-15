#ifndef PHY_H
#define PHY_H

#include <stdlib.h>
#include <stdint.h>

#include "comms_config.h"
#include "util.h"
#include "dll.h"

typedef struct {
    uint8_t chan_send;
    uint8_t chan_recv;
    unsigned noise;
} Physical;

// phy services
typedef DLL_frame (*recv_callback_phy)(void);
recv_callback_phy phy_phy(Physical* phy);
void send_phy(Physical* phy, DLL_frame dll_frame);

// phy debug functions
void print_phy(Physical* phy);

//internal methods
static Physical* __create_phy();
static void __destroy_phy(Physical* phy);
static void __send_phy_byte(Physical* phy, uint8_t byte);
static uint8_t __recv_phy_byte(Physical* phy);
static uint8_t __channel(Physical* phy);
static uint8_t __noise(Physical* phy, uint8_t byte);

#endif