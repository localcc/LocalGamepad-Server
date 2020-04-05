//
// Created by local on 02.04.2020.
//

#ifndef LOCALGAMEPAD_SERVER_UDP_SERVER_H
#define LOCALGAMEPAD_SERVER_UDP_SERVER_H

#include <map>
#include <memory>
#include <functional>
#include <controller/controller.h>

#ifdef WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#endif


class udp_server {
public:
    explicit udp_server(int port);
    void socket_listen();
    ~udp_server();
private:
    char last_client_id;
    static int init_windows();
    static void handle_connect(udp_server* server, sockaddr_in cli_addr, unsigned char* data);
    static void handle_data(udp_server* server, sockaddr_in cli_addr, unsigned char* data);
    static void handle_disconnect(udp_server* server, sockaddr_in cli_addr, unsigned char* data);
    int server_sock_fd;
    bool running;
    const std::map<uint8_t, std::function<void(udp_server*, const sockaddr_in, unsigned char* data)>> command_handlers = {
            {6, &handle_connect},
            {1, &handle_data},
            {9, &handle_disconnect}
    };
    std::map<unsigned char, std::unique_ptr<controller>> id_controller_mapping;
};

#endif //LOCALGAMEPAD_SERVER_UDP_SERVER_H
