#ifndef DLL_H
#define DLL_H

typedef struct {
   int temp; 
} DLL;

typedef struct {
    int temp;
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