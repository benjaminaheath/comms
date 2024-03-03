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
    // DLL details
    uint8_t DEV_ADDR;
    // receive buffer
    uint8_t* buf;
    size_t buf_size;
    enum buf_mode mode;
    // fragment buffer
    DLL_frame** frmbuf;
    size_t frmbuf_size;
    bool final_present;

} DLL;

typedef struct {
    // frame information
    uint8_t* frame;
    size_t frame_len;
    // parameter fields
    size_t CTRL_HIGH;
    size_t CTRL_LOW;
    size_t ADDR_SEND;
    size_t ADDR_RECV;
    size_t LENGTH;
    size_t PAYLOAD;
    size_t CHECKSUM_HIGH;
    size_t CHECKSUM_LOW;
} DLL_frame;

typedef void (*recv_callback_dll)(uint8_t);

typedef struct {
    uint8_t* packet;
    size_t pkt_size;
} NET_packet;

typedef void (*recv_callback_net)(NET_packet);

#endif