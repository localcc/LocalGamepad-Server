//
// Created by local on 02.04.2020.
//

#ifndef LOCALGAMEPAD_SERVER_CONTROLLER_H
#define LOCALGAMEPAD_SERVER_CONTROLLER_H

#ifdef WIN32
#include <ws2tcpip.h>
#include <winsock2.h>
#include <ViGEm/Common.h>
#include <ViGEm/Client.h>
#include <cstdio>

#endif

class controller {
public:
    controller(int sock_fd, sockaddr_in cli_addr): sock_fd{sock_fd}, cli_addr(cli_addr){}
    int handle();
private:
    int handle_windows();
    int handle_linux();
    int sock_fd;
    sockaddr_in cli_addr;
#ifdef WIN32
    PVIGEM_TARGET driver_target;
    PVIGEM_CLIENT driver_client;
#endif
};

#endif //LOCALGAMEPAD_SERVER_CONTROLLER_H
