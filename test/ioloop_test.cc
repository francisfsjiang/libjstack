#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "../src/IOLoop.h"
#include "../src/Event.h"
#include "../src/Log.h"

#define LISTEN_PORT 8000
#define LISTEN_ADDR "0.0.0.0"

void read_cb(int fd, int data) {
    std::cout << "read_cb fd = " << fd << "data = " << data << std::endl;
}

void write_cb(int fd, int data) {
    std::cout << "write_cb fd = " << fd << "data = " << data << std::endl;
}

int main() {
    int socket_fd, ret;
    struct sockaddr_in sock_addr;

    socket_fd = socket(PF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0) {
        std::cout << "socket create failed." << std::endl;
        exit(EXIT_FAILURE);
    }

    sock_addr.sin_family = PF_INET;
    sock_addr.sin_port = htons(LISTEN_PORT);
    sock_addr.sin_addr.s_addr = htonl(inet_addr(LISTEN_ADDR));

    ret = bind(socket_fd, (struct sockaddr *) &sock_addr, sizeof(sock_addr));
    if (ret < 0) {
        std::cout << "socket bind failed. %s" << std::endl;
        exit(EXIT_FAILURE);
    }

    ret = listen(socket_fd, 8);
    if (ret < 0) {
        std::cout << "socket listen failed." << std::endl;
        exit(EXIT_FAILURE);
    }

    LOG_DEBUG << "listen fd=" << socket_fd;

    dc::Event e(socket_fd);
    e.set_read_call_back(read_cb);
    e.set_write_call_back(write_cb);

    dc::IOLoop::Current()->AddEvent(e);
    dc::IOLoop::Current()->Loop();
    return 0;
}