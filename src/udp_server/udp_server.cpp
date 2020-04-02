//
// Created by local on 02.04.2020.
//

#include <udp_server/udp_server.h>
#include <udp_server/udp_client.h>
#include <cstdio>
#include <memory>

udp_server::udp_server(int port) {
int res = 0;
    #ifdef WIN32
    res = init_windows();
    if(res < 0) printf("Failed to init wsa: %d\n", res);
    #endif
    this->server_sock_fd = socket(AF_INET, SOCK_DGRAM, NULL);
    if(this->server_sock_fd < 0) {
        printf("socket() fail!\n");
        return;
    }
    struct sockaddr_in srv_addr;
    memset(&srv_addr, 0, sizeof(srv_addr));
    srv_addr.sin_port = htons(port);
    srv_addr.sin_family = AF_INET;
    srv_addr.sin_addr.s_addr = INADDR_ANY;
    if(bind(this->server_sock_fd, reinterpret_cast<struct sockaddr*>(&srv_addr), sizeof(srv_addr)) < 0) {
        printf("bind() fail!\n");
        return;
    }
}

int udp_server::socket_listen() {
    if(listen(this->server_sock_fd, NULL) < 0) {
        return -81;
    }
    this->running = true;
    while(this->running) {
        struct sockaddr_in cli_addr;
        socklen_t cli_len = sizeof(cli_addr);
        int client_sock_fd = accept(this->server_sock_fd, reinterpret_cast<struct sockaddr*>(&cli_addr), &cli_len);
        if(client_sock_fd < 0) {
            printf("accept() failed!\n");
        } else {
            auto client = std::make_unique<udp_client>(client_sock_fd, cli_addr);

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