#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdint.h>
#include <stdbool.h>

enum buf_mode {
    WAIT,
    LISTEN,
    ESCAPE
};

typedef enum frm_type {
    ACK  = 0b00,
    NACK = 0b01,
    MSG  = 0b10
} frm_type_t;

typedef void (*recv_callback_phy)(uint8_t);

typedef struct {
    recv_callback_phy recv_phy;
    uint8_t* buf;
    unsigned int buf_size;
    unsigned int buf_end;
    enum buf_mode mode;
} DLL;

typedef struct {
    uint8_t* frame;
    size_t frame_len;
} DLL_frame;

typedef struct {
    uint8_t* packet;
    size_t pkt_size;
} NET_packet;

typedef void (*recv_callback_dll)(uint8_t);

#endif