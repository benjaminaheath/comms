#ifndef DLL_H
#define DLL_H

#include <stdint.h>
#include <stdlib.h>

#include "comms_config.h"
#include "structs.h"
#include "util.h"

#include "net.h"
#include "phy.h"

// dll helper functions
void create_dll(DLL* dll);
void destroy_dll(DLL* dll);

// dll services
void send_dll(NET_packet pkt);
recv_callback_dll link_dll();
NET_packet recv_dll();
void service_dll(Physical* phy, DLL* dll);
void close_dll();

// dll internal methods
static void __buf_write(DLL* dll, uint8_t byte);
static uint8_t __buf_read(DLL* dll, unsigned int index);
static void __buf_flush(DLL* dll);
static uint8_t __get_num_pkt_fragments(uint8_t pkt_length, uint8_t max_length);
static uint8_t* __get_len_pkt_fragments(uint8_t pkt_length, uint8_t max_length);
static uint8_t** __get_pkt_fragments(uint8_t* len_fragments, uint8_t num_fragments, uint8_t* pkt, size_t len_pkt);

#endif