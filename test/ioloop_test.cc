#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "../src/IOLoop.h"
#include "../src/Event.h"

#define LISTEN_PORT 8000
#define LISTEN_ADDR "0.0.0.0"

void read_cb(int fd) {
    std::cout<<"read_cb "<<fd<<std::endl;
}

void write_cb(int fd) {
    std::cout<<"write_cb "<<fd<<std::endl;
}

int main() {
    int socket_fd, ret;
    struct sockaddr_in sock_addr;
    dc::IOLoop ioloop;

    socket_fd = socket(PF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0) {
        std::cout<<"socket create failed."<<std::endl;
        exit(EXIT_FAILURE);
    }

    sock_addr.sin_family = PF_INET;
    sock_addr.sin_port = htons(LISTEN_PORT);
    sock_addr.sin_addr.s_addr = htonl(inet_addr(LISTEN_ADDR));

    ret = bind(socket_fd, (struct sockaddr *)&sock_addr, sizeof(sock_addr));
    if (ret < 0) {
        std::cout<< "socket bind failed. %s"<<std::endl;
        exit(EXIT_FAILURE);
    }

    ret = listen(socket_fd, 8);
    if (ret < 0) {
        std::cout<<"socket listen failed."<<std::endl;
        exit(EXIT_FAILURE);
    }

    dc::Event eve(socket_fd);
    eve.set_read_call_back(read_cb);
    eve.set_write_call_back(write_cb);

    return 0;
}