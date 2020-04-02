//
// Created by local on 02.04.2020.
//

#include <controller/controller.h>
#include <controller/controller_conversions.h>
#include <cstdio>

int controller::handle() {
#ifdef WIN32
    return handle_windows();
#else
    return handle_linux();
#endif
}

int controller::handle_windows() {
    this->driver_client = vigem_alloc();
    this->driver_target = vigem_target_x360_alloc();
    if (vigem_connect(this->driver_client) != VIGEM_ERROR_NONE) return -80;
    if (vigem_target_add(this->driver_client, this->driver_target) != VIGEM_ERROR_NONE) return -81;
    char* recv_buf = new char[14];
    int cli_len = sizeof(this->cli_addr);
    int recv_len = 0;
    do {
        memset(recv_buf, 0, 14);
        recv_len = recvfrom(this->sock_fd, recv_buf, 14, NULL, reinterpret_cast<sockaddr*>(&this->cli_addr), &cli_len);
        if(recv_len <= 0) break;
        vigem_target_x360_update(this->driver_client, this->driver_target, controller_conversions::data_to_report(recv_buf));
    }while(recv_len > 0);
    delete recv_buf;
    vigem_target_remove(this->driver_client, this->driver_target);
    vigem_disconnect(this->driver_client);
    vigem_target_free(this->driver_target);
    vigem_free(this->driver_client);
}
int controller::handle_linux() {
    //TODO: realization
    return 0;
}