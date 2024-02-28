#ifndef PHY_H
#define PHY_H

#include <stdlib.h>
#include <stdint.h>

#include "comms_config.h"
#include "structs.h"
#include "util.h"
#include "dll.h"



// phy services
recv_callback_phy phy_phy();
void send_phy(uint8_t byte, recv_callback_phy recv);

// phy internal methods
static void recv_phy(uint8_t byte);
static uint8_t __channel(uint8_t byte);
static uint8_t __noise(uint8_t byte);

#endif