#include "main.h"

int main() {
    Physical* phy = create_phy();
    Sim* sim = create_sim(phy);
    for(int i=0; i<10; ++i){
        send_phy_byte(phy,0xFF);
        recv_phy_byte(phy);
        print_sim(sim);
        update_sim(sim);
    }
    return 0;
}