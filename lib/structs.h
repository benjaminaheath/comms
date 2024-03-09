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
    // frame information
    uint8_t* frame;   // Pointer to start of frame
    size_t frame_len; // Length of frame in bytes

    // field pointers
    uint8_t* PTR_CTRL_HIGH;  // Pointer to CTRL_HIGH byte
    uint8_t* PTR_CTRL_LOW;   // Pointer to CTRL_LOW byte
    uint8_t* PTR_ADDR_SEND;  // Pointer to ADDR_SEND byte
    uint8_t* PTR_ADDR_RECV;  // Pointer to ADDR_RECV byte
    uint8_t* PTR_LENGTH;     // Pointer to LENGTH byte
    uint8_t* PTR_PAYLOAD;    // Pointer to Payload
    uint8_t* PTR_CHECK_HIGH; // Pointer to CHECK_HIGH byte
    uint8_t* PTR_CHECK_LOW;  // Pointer to CHECK_LOW byte

    // frame parameters
    uint8_t FRAGMENT;    // CTRL fragment number
    bool FINAL;          // CTRL final flag
    bool PROTOCOL;       // CTRL protocol flag
    frm_type_t MSG_TYPE; // CTRL message type flag
    bool CHECKTYPE;      // CTRL checksum type flag
    uint8_t SEQ_NUM;     // CTRL sequence number
    uint8_t ADDR_SEND;   // DLL Sender MAC Address
    uint8_t ADDR_RECV;   // DLL Receiver MAC Address
    uint8_t LENGTH;      // Payload Length
    uint8_t* PAYLOAD;
    uint16_t CHECKSUM;   // Checksum
} DLL_frame;

typedef struct {
    // DLL details
    uint8_t DEV_ADDR; // DLL MAC Address

    // receive buffer
    uint8_t* buf;       // DLL Frame Receive Buffer
    size_t buf_size;    // DLL Frame Receive Buffer Size
    enum buf_mode mode; // DLL Frame Receive Buffer State

    // fragment buffer
    DLL_frame** frmbuf; // DLL Fragment Storage Buffer
    size_t frmbuf_size; // DLL Fragment Storage Buffer Size
    bool first_present; // First Fragment Present Flag
    bool final_present; // Final Fragment Present Flag
} DLL;

typedef void (*recv_callback_dll)(uint8_t);

typedef struct {
    uint8_t* packet;
    size_t pkt_size;
} NET_packet;

typedef void (*recv_callback_net)(NET_packet);

#endif