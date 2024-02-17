#include "main.h"

int main() {
    // set up physical instance and link callback
    Physical* phy = create_phy();
    recv_callback_phy phy_recv = phy_phy(phy);

    //link DLL callback 
    recv_callback_dll dll_recv = link_dll();

    DLL_frame test_frame = {90};
    send_phy(phy, test_frame);
    DLL_frame test_frame_recv = phy_recv(phy);

    printf("Post transmit bytes:");
    print_byte(test_frame.frame);
    print_byte(test_frame_recv.frame);
    return 0;
}