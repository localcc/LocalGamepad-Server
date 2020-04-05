#include <iostream>
#include <udp_server/udp_server.h>
#include <thread>

int main() {
    auto server = std::make_shared<udp_server>(5781);
    std::thread([&](){
        server->socket_listen();
    }).detach();
    while(true){}
    return 0;
}
