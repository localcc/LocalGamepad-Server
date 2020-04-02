//
// Created by local on 02.04.2020.
//

#include <udp_server/udp_server.h>
#include <controller/controller.h>
#include <cstdio>
#include <memory>
#include <thread>


udp_server::udp_server(int port) {
int res = 0;
    #ifdef WIN32
    res = init_windows();
    if(res < 0) printf("Failed to init wsa: %d\n", res);
    #endif
    this->server_sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(this->server_sock_fd < 0) {
        printf("socket() fail!\n");
        return;
    }
    sockaddr_in srv_addr;
    memset(&srv_addr, 0, sizeof(srv_addr));
    srv_addr.sin_port = htons(port);
    srv_addr.sin_family = AF_INET;
    srv_addr.sin_addr.s_addr = INADDR_ANY;
    if(bind(this->server_sock_fd, reinterpret_cast<sockaddr*>(&srv_addr), sizeof(srv_addr)) < 0) {
        printf("bind() fail!\n");
        return;
    }

}

int udp_server::socket_listen() {
    this->running = true;
    while (this->running) {
        sockaddr_in cli_addr;
        int cli_addr_len = sizeof(cli_addr);
        char *auth_buf = new char[4];
        memset(&cli_addr, 0, cli_addr_len);
        memset(auth_buf, 0, 4);
        recvfrom(this->server_sock_fd, auth_buf, 4, 0, reinterpret_cast<sockaddr *>(&cli_addr), &cli_addr_len);
        if (auth_buf[0] == 1 && auth_buf[1] == 4 && auth_buf[2] == 2 && auth_buf[3] == 9) {
            // Creating a client
            std::thread([&]{(new controller(this->server_sock_fd, cli_addr))->handle();}).detach();
        }
    }
    return 0;
}

udp_server::~udp_server() {
    #ifdef WIN32
    WSACleanup();
    #endif
}
int udp_server::init_windows() {
    WSAData wsaData;
    int res = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if(res != 0) {
        return res;
    }
    return 0;
}