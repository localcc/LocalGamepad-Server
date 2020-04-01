//
// Created by local on 02.04.2020.
//

#include <controller/controller.h>

controller::controller(std::unique_ptr<udp_client> client) {

}


void controller::handle() {
#ifdef WIN32
    windows_handle();
#else
    linux_handle();
#endif
}

void controller::windows_handle() {

}

void controller::linux_handle() {

}


controller::~controller() {

}


