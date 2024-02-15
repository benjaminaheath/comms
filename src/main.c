#include "main.h"

int main() {
    Physical* phy = create_phy();
    Sim* sim = create_sim(phy);
    print_sim(sim);
    return 0;
}