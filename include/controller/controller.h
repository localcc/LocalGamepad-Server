//
// Created by local on 02.04.2020.
//

#ifndef LOCALGAMEPAD_SERVER_CONTROLLER_H
#define LOCALGAMEPAD_SERVER_CONTROLLER_H
#include <cstdio>

#ifdef WIN32
#include <ws2tcpip.h>
#include <winsock2.h>
#include <ViGEm/Common.h>
#include <ViGEm/Client.h>
#endif

class controller {
public:
    controller() = default;
    int handle(unsigned char* data);
    int init();
    void uninit() const;
private:
    int init_windows();
    int handle_windows(unsigned char* data);
    void stop_windows() const;
#ifdef WIN32
    PVIGEM_TARGET driver_target{};
    PVIGEM_CLIENT driver_client{};
#endif
};

#endif //LOCALGAMEPAD_SERVER_CONTROLLER_H
