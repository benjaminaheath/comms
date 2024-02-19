#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint8_t chan_recv;
    bool byte_recv;
    unsigned noise;
} Physical;

typedef struct {
    recv_callback_phy recv_phy;
    uint8_t* frame_buf;
    size_t frame_buf_size;
} DLL;

typedef struct {
    uint8_t frame;
} DLL_frame;

typedef struct {
    uint8_t packet;
} NET_packet;

typedef uint8_t (*recv_callback_phy)(Physical*);
typedef NET_packet (*recv_callback_dll)();

#endif