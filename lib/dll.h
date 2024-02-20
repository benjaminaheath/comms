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
void service_dll(Physical* phy, DLL* dll);
void close_dll();

// dll internal methods
static void __buf_write(DLL* dll, uint8_t byte);
static uint8_t __buf_read(DLL* dll, unsigned int index);
static void __buf_flush(DLL* dll);
#endif