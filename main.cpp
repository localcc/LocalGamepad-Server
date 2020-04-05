#include <iostream>
#include <udp_server/udp_server.h>
#include <thread>
#include <csignal>

volatile bool running = false;

void signal_handler(int signal) {
    if(signal == SIGINT) {
        running = false;
    }
}

int main(int argc, char* argv[]) {
    if(argc < 2) {
        printf("Not enough arguments!\n Example: LocalGamepadServer [port]");
        return -1;
    }
    auto server = std::make_shared<udp_server>(atoi(argv[1]));
    std::thread t1([&](){
        server->socket_listen();
    });
    t1.detach();
    signal(SIGINT, signal_handler);
    running = true;
    while(running){}
    server->stop();
    server.reset();
    return 0;
}
