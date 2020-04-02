//
// Created by local on 02.04.2020.
//

#ifndef LOCALGAMEPAD_SERVER_UDP_SERVER_H
#define LOCALGAMEPAD_SERVER_UDP_SERVER_H

#include <map>
#include <memory>

#ifdef WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#endif


class udp_server {
public:
    udp_server(int port);
    int socket_listen();
    ~udp_server();
private:
    int init_windows();
    int server_sock_fd;
    bool running;
};

#endif //LOCALGAMEPAD_SERVER_UDP_SERVER_H
