#ifndef NET_H
#define NET_H

#include <stdint.h>

#include "structs.h"

recv_callback_net link_net();
void recv_net(NET_packet pkt);

#endif 