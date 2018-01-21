#include "abathur/tcp/tcp_server.h"

#include <cstring>

#include "abathur/io_loop.h"
#include "abathur/event_callback.h"
#include "abathur/tcp/tcp_connection.h"
#include "abathur/tcp/tcp_handler.h"

namespace abathur {
namespace tcp {


//TCPServer::TCPServer() {
//
//}

void TCPServer::CreateConnection(int fd, int data) {

#if defined(__linux__)
    if (data == -1) data = 1;
#endif

#if defined(ABATHUR_DEBUG)
    LOG_DEBUG << "fd" << fd << " has " << data << " connections";
#endif

    sockaddr sock_addr;
    socklen_t sock_addr_len;

    for (int i = 0; i < data; ++i) {

        int coon_fd = accept(fd, &sock_addr, &sock_addr_len);
        TCPConnection *coon;

        string from_address;
        if (sock_addr.sa_family == PF_UNIX) {
            from_address += sock_addr.sa_data;
        }
        else {
            from_address += inet_ntoa(((sockaddr_in *) &sock_addr)->sin_addr);
            from_address += ":";
            from_address += std::to_string(htons(((sockaddr_in *) &sock_addr)->sin_port));
        }

        LOG_INFO << "fd" << fd
        << " Incoming connection from "
        << from_address;

        coon = new TCPConnection(coon_fd,
                                 from_address,
                                 route_map_[fd],
                                 this);


        connection_poll_.insert(make_pair(coon_fd, coon));


    }

}

void TCPServer::_AddHandler(const sockaddr &sock_addr, function<void *()> func) {
    int sock_fd, ret;
    if (sock_addr.sa_family != PF_UNIX &&
        sock_addr.sa_family != PF_INET) {
        LOG_ERROR << "Target protocol supported" << sock_addr.sa_family;
        throw util::SocketError("bind failed");
    }

    sock_fd = socket(sock_addr.sa_family, SOCK_STREAM, 0);
    if (sock_fd < 0) {
        LOG_ERROR << " socket create failed" << sock_addr.sa_data << strerror(errno);
        throw util::SocketError("socket create failed");
    }

    ret = ::bind(sock_fd, &sock_addr, sizeof(sock_addr));
    if (ret < 0) {
        LOG_ERROR << sock_fd << " bind failed" << sock_addr.sa_data << strerror(errno);
        throw util::SocketError("bind failed");
    }

    ret = listen(sock_fd, MAX_PENDING_CONNECTIONS_NUM);
    if (ret < 0) {
        LOG_ERROR << sock_fd << " listen failed" << sock_addr.sa_data << strerror(errno);
        throw util::SocketError("listen failed");
    }

    route_map_.insert(std::make_pair(sock_fd, func));

    EventCallback e;
    e.SetReadCallback(
            [this](const int& fd, const int& data){this->CreateConnection(fd, data);}
    );

    abathur::IOLoop::Current()->AddEventCallback(sock_fd, e);

#if defined(ABATHUR_DEBUG)
    LOG_DEBUG << "fd" << sock_fd << " Listen established";
#endif

    if (sock_addr.sa_family == PF_UNIX) {
        LOG_INFO << "Listen event on " << sock_addr.sa_data << " successfully";
    }
    else if (sock_addr.sa_family == PF_INET) {
        sockaddr_in *in_addr = (sockaddr_in *) (&sock_addr);
        LOG_INFO << "Listen event on "
        << inet_ntoa(in_addr->sin_addr)
        << ":"
        << ntohs(in_addr->sin_port)
        << " successfully";
    }
}


void TCPServer::RemoveConnection(int fd) {
    connection_poll_.erase(fd);
}

}
}
