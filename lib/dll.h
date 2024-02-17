#ifndef DLL_H
#define DLL_H

#include "net.h"

#include <stdint.h>

typedef struct {
    uint8_t frame;
} DLL_frame;

typedef NET_packet (*recv_callback_dll)();

// dll services
void send_dll();
recv_callback_dll link_dll();
NET_packet recv_dll();
void service_dll();
void close_dll();

#endif