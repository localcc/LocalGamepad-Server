#include <iostream>
#include <udp_server/udp_server.h>

int main() {
    auto server = std::make_shared<udp_server>(5781);
    int res = server->socket_listen();
    printf("%d\n", res);

    return 0;
}
