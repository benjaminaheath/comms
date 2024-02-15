#ifndef SIM_H
#define SIM_H

#include <stdio.h>

#include "phy.h"
typedef struct {
    unsigned long ticks; 
    Physical* sim_phy;
} Sim;

Sim* create_sim(Physical* sim_phy);
void print_sim(Sim* sim);
void destroy_sim(Sim* sim);

#endif 