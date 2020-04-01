//
// Created by local on 02.04.2020.
//

#ifndef LOCALGAMEPAD_SERVER_UDP_CLIENT_H
#define LOCALGAMEPAD_SERVER_UDP_CLIENT_H

#ifdef WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#endif

class udp_client {
public:
    udp_client(int sock_fd, sockaddr_in cli_addr): sock_fd(sock_fd), cli_addr(cli_addr){}
    int read_data(void* buf, int count);
    int write_data(void* buf, int count);
private:
    int sock_fd;
    sockaddr_in cli_addr;

};

#endif //LOCALGAMEPAD_SERVER_UDP_CLIENT_H
