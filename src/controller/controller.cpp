//
// Created by local on 02.04.2020.
//

#include <controller/controller.h>
#ifdef WIN32
#include <ViGEm/Common.h>
#include <ViGEm/Client.h>
#endif


controller::controller(std::unique_ptr<udp_client> client) {

}


void controller::handle() {
#ifdef WIN32
    windows_handle(0);
#else
    linux_handle();
#endif
}

int controller::windows_handle(int type) {
    PVIGEM_CLIENT driver_client = vigem_alloc();
    PVIGEM_TARGET driver_target = vigem_target_x360_alloc();

    return 0;
}

void controller::linux_handle() {

}


controller::~controller() {

}


