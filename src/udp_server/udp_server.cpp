//
// Created by local on 02.04.2020.
//

#include <udp_server/udp_server.h>
#include <controller/controller.h>
#include <cstdio>
#include <memory>


udp_server::udp_server(int port): last_client_id(0), running(false) {
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
    sockaddr_in srv_addr{};
    memset(&srv_addr, 0, sizeof(srv_addr));
    srv_addr.sin_port = htons(port);
    srv_addr.sin_family = AF_INET;
    srv_addr.sin_addr.s_addr = INADDR_ANY;
    if(bind(this->server_sock_fd, reinterpret_cast<sockaddr*>(&srv_addr), sizeof(srv_addr)) < 0) {
        printf("bind() fail!\n");
        return;
    }

}

void udp_server::socket_listen() {
    this->running = true;

    sockaddr_in cli_addr{};
    int cli_addr_len = sizeof(cli_addr);
    memset(&cli_addr, 0, cli_addr_len);
    auto* buf = new unsigned char[16];
    while (this->running) {
        memset(buf, 0, 16);
        // Reading 16 so every type of command will fit
        recvfrom(this->server_sock_fd, reinterpret_cast<char *>(buf), 16, NULL, reinterpret_cast<sockaddr *>(&cli_addr), &cli_addr_len);
        auto search = this->command_handlers.find(buf[0]);
        if(search != this->command_handlers.end()) {
            search->second(this, cli_addr, buf + 1);
        }
    }
    delete[] buf;
}

void udp_server::stop() {
    this->running = false;
}

void udp_server::handle_connect(udp_server *server, sockaddr_in cli_addr, unsigned char* data) {
    if(data[0] == 6 && data[1] == 4 && data[2] == 2 && data[3] == 9) {
        auto controller_instance = std::make_unique<controller>();
        int res = controller_instance->init();
        if(res < 0) {
            printf("controller_instance->init() failed: %d\n", res);
            return;
        }
        server->id_controller_mapping.emplace(server->last_client_id, std::move(controller_instance));
        auto* resp_buf = new unsigned char[2];
        resp_buf[0] = 2;
        resp_buf[1] = server->last_client_id;
        sendto(server->server_sock_fd, reinterpret_cast<const char*>(resp_buf), 2, NULL, reinterpret_cast<sockaddr*>(&cli_addr), sizeof(cli_addr));
        server->last_client_id++;
    }
}

void udp_server::handle_disconnect(udp_server* server, sockaddr_in cli_addr, unsigned char* data) {
    auto search = server->id_controller_mapping.find(data[0]);
    if(search != server->id_controller_mapping.end()) {
        search->second->uninit();
    }
}

void udp_server::handle_data(udp_server *server, sockaddr_in cli_addr, unsigned char* data) {
    auto search = server->id_controller_mapping.find(data[0]);
    if(search != server->id_controller_mapping.end()) {
        // adding 1 to pointer so data would be handled correctly
        printf("Data\n");
        search->second->handle(data + 1);
    }
}

udp_server::~udp_server() {
    #ifdef WIN32
    WSACleanup();
    #endif
}

int udp_server::init_windows() {
    WSAData wsaData{};
    int res = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if(res != 0) {
        return res;
    }
    return 0;
}
