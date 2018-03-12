#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
//#include <arpa/inet.h>
#include <unistd.h>

#include "abathur/abathur.hpp"
#include "abathur/io_loop.hpp"

#define LISTEN_PORT 8001
#define LISTEN_ADDR "0.0.0.0"

using namespace abathur;

char buffer[1000];


void read_cb(int fd, int data) {
    read(fd, buffer, data);
    buffer[data + 1] = '\0';
    std::cout << "read_cb fd = " << fd << "data = " << buffer << std::endl;
}

void write_cb(int fd, int data) {
    std::cout << "write_cb fd = " << fd << "data = " << data << std::endl;
}

void close_cb(int fd, int data) {
    std::cout << "close_cb fd = " << fd << "data = " << data << std::endl;
}

void accept_cb(int fd, int data) {
    std::cout << "accept_cb fd = " << fd << "data = " << data << std::endl;
    sockaddr sock_addr;
    socklen_t sock_addr_len;

    for (int i = 0; i < data; ++i) {
        int coon_fd = accept(fd, (sockaddr *) &sock_addr, &sock_addr_len);
        std::cout << "from " << sock_addr.sa_data << std::endl;

        std::cout << "add conn " << coon_fd << std::endl;

        EventCallback e;
        e.SetReadCallback(read_cb);
        e.SetWriteCallback(write_cb);
        e.SetCloseCallback(close_cb);

        abathur::IOLoop::Current()->AddEventCallback(coon_fd, e);
    }
}


int main() {
    int socket_fd, ret;
    sockaddr sock_addr;

    socket_fd = socket(PF_UNIX, SOCK_STREAM, 0);
    if (socket_fd < 0) {
        std::cout << "socket create failed." << std::endl;
        exit(EXIT_FAILURE);
    }
    sock_addr.sa_family = PF_UNIX;
    strcpy(sock_addr.sa_data, "test.sock\0");

    ret = ::bind(socket_fd, &sock_addr, sizeof(sock_addr));
    if (ret < 0) {
        std::cout << "socket bind failed." << std::endl;
        exit(EXIT_FAILURE);
    }

    ret = listen(socket_fd, 8);
    if (ret < 0) {
        std::cout << "socket listen failed." << std::endl;
        exit(EXIT_FAILURE);
    }

    LOG_DEBUG << "listen fd=" << socket_fd;

    EventCallback e;
    e.SetReadCallback(read_cb);
    e.SetWriteCallback(write_cb);

    abathur::IOLoop::Current()->AddEventCallback(socket_fd, e);
    abathur::IOLoop::Current()->Loop();
    return 0;
}