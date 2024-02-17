#ifndef DLL_H
#define DLL_H

#include <stdint.h>

typedef struct {
   int temp; 
} DLL;

typedef struct {
    uint8_t frame;
} DLL_frame;

// dll constructor and destructor
DLL* create_dll();
void destroy_dll();

// dll services
void send_dll();
void link_dll();
void service_dll();
void close_dll();

#endif