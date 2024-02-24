#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "comms_config.h"

// helper utilities
void print_bytes(uint8_t* bytes, size_t num_bytes);
void print_byte(uint8_t byte);
uint8_t* rand_bytes(size_t num_bytes);
uint8_t rand_byte();
uint8_t* append_byte(uint8_t* bytes, size_t num_bytes, uint8_t new_byte);
uint8_t* append_bytes(uint8_t* bytes, size_t num_bytes, uint8_t* new_bytes, size_t num_new_bytes);
// internal functions
static void __print(uint8_t byte);
#endif