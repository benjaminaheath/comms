#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "comms_config.h"

// helper utilities
void print_bytes(uint8_t* bytes, size_t num_bytes);
void print_byte(uint8_t byte);
void print_ptr(void* ptr);

uint8_t* rand_bytes(size_t num_bytes);
uint8_t rand_byte();

void append_byte(uint8_t** bytes, size_t* num_bytes, uint8_t new_byte);
void append_bytes(uint8_t** bytes, size_t* num_bytes, uint8_t* new_bytes, size_t num_new_bytes);

uint8_t get_byte(uint8_t* bytes, size_t num_bytes, size_t index);
uint8_t* get_bytes_from(uint8_t* bytes, size_t num_bytes, size_t index_start, size_t num_in_range);
uint8_t* get_bytes_range(uint8_t* bytes, size_t num_bytes, size_t index_start, size_t index_end);

// internal functions
static void __print(uint8_t byte);
#endif