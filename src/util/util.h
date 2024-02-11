#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdint.h>

#include "comms_config.h"

void print_bytes(uint8_t* bytes, size_t num_bytes);
void print_byte(uint8_t byte);
static void __print(uint8_t byte);
#endif