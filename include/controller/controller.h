//
// Created by local on 02.04.2020.
//

#ifndef LOCALGAMEPAD_SERVER_CONTROLLER_H
#define LOCALGAMEPAD_SERVER_CONTROLLER_H
#include <udp_server/udp_client.h>
#include <memory>

class controller {
public:
    explicit controller(std::unique_ptr<udp_client> client);
    void handle();
    ~controller();
private:
    void windows_handle();
    void linux_handle();
    std::unique_ptr<udp_client> client;
};

#endif //LOCALGAMEPAD_SERVER_CONTROLLER_H
