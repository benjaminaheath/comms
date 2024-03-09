#ifndef DLL_H
#define DLL_H

#include <stdint.h>
#include <stdlib.h>

#include "comms_config.h"
#include "structs.h"
#include "util.h"

#include "net.h"
#include "phy.h"

// dll services
void send_dll(NET_packet pkt);
recv_callback_dll link_dll();
void service_dll();
void close_dll();

// dll frame helpers
void __frame_dll(DLL_frame *frm);
DLL_frame __deframe_dll(uint8_t* frm, size_t frm_size);

// dll internal methods -- send
static uint8_t __get_num_pkt_fragments(uint8_t pkt_length, uint8_t max_length);
static uint8_t* __get_len_pkt_fragments(uint8_t pkt_length, uint8_t max_length);
static uint8_t** __get_pkt_fragments(uint8_t* len_fragments, uint8_t num_fragments, uint8_t* pkt, size_t len_pkt);
static uint16_t __get_control_subframe(DLL_frame frm);
static uint16_t __get_checksum_subframe(uint8_t* frame, size_t frame_len);
static uint16_t __get_CRC16(uint8_t* frame, size_t frame_len);
static uint16_t __get_parity(uint8_t* frame, size_t frame_len);
static void __escape_frame(uint8_t** frame, size_t* frame_len);

// dll internal methods -- receive
void recv_dll(uint8_t byte);
static void __recv_frame();
static void __store_fragment(DLL_frame* frm, uint8_t fragment, uint8_t seq, bool final);
static bool __check_complete_pkt();
static NET_packet __reconstruct_pkt();
#endif