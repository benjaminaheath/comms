#ifndef PHY_H
#define PHY_H

#include <stdlib.h>
#include <stdint.h>

#include "comms_config.h"
#include "util.h"

typedef struct {
    uint8_t chan_send;
    uint8_t chan_recv;
    unsigned noise;
} Physical;

// phy constructor and destructor
Physical* create_phy();
void destroy_phy(Physical* phy);

// phy debug functions
void send_phy_byte(Physical* phy, uint8_t byte);
uint8_t recv_phy_byte(Physical* phy);
void print_phy(Physical* phy);

// phy services
void send_phy();
void phy_phy();

//internal methods
static uint8_t __channel(Physical* phy);
static uint8_t __noise(Physical* phy, uint8_t byte);

#endif