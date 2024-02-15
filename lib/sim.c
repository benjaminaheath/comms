#include "sim.h"

Sim* create_sim(Physical* sim_phy) {
    Sim* sim = (Sim*) malloc(sizeof(Sim));
    sim->ticks = 0;
    sim->sim_phy = sim_phy;
    return sim;
}

void update_sim(Sim* sim) {
    sim->ticks += 1;
}

void print_sim(Sim* sim) {
    printf("%lu: ",sim->ticks);
    print_phy(sim->sim_phy);
}

void destroy_sim(Sim* sim) {
    free(sim->sim_phy);
    free(sim);
}