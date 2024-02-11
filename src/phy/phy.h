#ifndef PHY_H
#define PHY_H

#include <stdlib.h>
#include <stdint.h>

#include "comms_config.h"
#include "util.h"

typedef struct {
    uint8_t chan_send;
    uint8_t chan_recv;
} Physical;

Physical* create_phy();
void destroy_phy(Physical* phy);
void send_phy(Physical* phy, uint8_t byte);
uint8_t recv_phy(Physical* phy);
void print_phy(Physical* phy);


#endif