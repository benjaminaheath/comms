#include "main.h"

int main() {
    // set up physical instance and link callback
    Physical* phy = create_phy();
    recv_callback_phy phy_recv = phy_phy(phy);

    //link DLL callback 
    recv_callback_dll dll_recv = link_dll();

    return 0;
}