#ifndef SIM_H
#define SIM_H

#include "phy.h"

typedef struct {
    unsigned long ticks; 
    Physical* sim_phy;
} Sim;

#endif 