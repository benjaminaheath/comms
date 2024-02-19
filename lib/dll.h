#ifndef DLL_H
#define DLL_H

#include <stdint.h>

#include "comms_config.h"
#include "net.h"
#include "structs.h"

// dll helper functions
void create_dll(DLL* dll);
void destroy_dll(DLL* dll);

// dll services
void send_dll();
recv_callback_dll link_dll();
NET_packet recv_dll();
void service_dll(DLL* dll);
void close_dll();

// dll internal methods

#endif