#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdint.h>
#include <stdbool.h>

typedef void (*recv_callback_phy)(uint8_t);

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

typedef struct {
    // receive buffer
    uint8_t* buf;
    size_t buf_size;
    enum buf_mode mode;
    // frame buffer
    DLL_frame* frmbuf;
    size_t frmbuf_size;


} DLL;

typedef struct {
    uint8_t* frame;
    size_t frame_len;
} DLL_frame;

typedef void (*recv_callback_dll)(uint8_t);

typedef struct {
    uint8_t* packet;
    size_t pkt_size;
} NET_packet;

typedef void (*recv_callback_net)(NET_packet);

#endif