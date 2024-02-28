#include "sim.h"

Sim* create_sim() {
    Sim* sim = (Sim*) malloc(sizeof(Sim));
    sim->ticks = 0;
    return sim;
}

void update_sim(Sim* sim) {
    sim->ticks += 1;
}

void print_sim(Sim* sim) {
    printf("%lu: ",sim->ticks);
}

void destroy_sim(Sim* sim) {
    free(sim);
}