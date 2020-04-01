//
// Created by local on 02.04.2020.
//

#include <udp_server/udp_client.h>

int udp_client::read_data(void* buf, int count) {
sockaddr_in from;
int size = sizeof(from);
int ret = 0;
#ifdef WIN32
ret = recvfrom(sock_fd, reinterpret_cast<char*>(buf), count, NULL, reinterpret_cast<sockaddr*>(&from), &size);
#else
ret = recvfrom(sock_fd, buf, count, NULL, reinterpret_cast<sockaddr*>(&from), &size);
#endif
return ret;
}

int udp_client::write_data(void* buf, int count) {
#ifdef WIN32
return sendto(this->sock_fd, reinterpret_cast<char*>(buf), count, NULL, reinterpret_cast<sockaddr*>(&cli_addr), sizeof(cli_addr));
#else
return sendto(this->sock_fd, buf, count, NULL, reinterpret_cast<sockaddr*>(&cli_addr), sizeof(cli_addr);
#endif
}

