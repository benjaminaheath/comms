#ifndef SIM_H
#define SIM_H

#include <stdio.h>

#include "phy.h"

typedef struct {
    unsigned long ticks; 
} Sim;

Sim* create_sim();
void update_sim(Sim* sim);
void print_sim(Sim* sim);
void destroy_sim(Sim* sim);

#endif 