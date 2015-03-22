//
// Created by Neveralso on 15/3/19.
//

#include "TCPServer.h"

#include <string>

#include "../Log.h"
#include "../util/error.h"

namespace dc {

template<typename T>
void TCPServer::AddHandler(const struct sockaddr &sock_addr) {

    if (!std::is_base_of<TCPHandler, T>::value) {
        LOG_ERROR << "Wrong handler type" << typeid(T).name();
        throw HandlerTypeError(typeid(T).name());
    }

    int sock_fd, ret;
    if (sock_addr.sa_family != PF_UNIX &&
        sock_addr.sa_family != PF_INET) {
        LOG_ERROR << "Target protocol supported. " << sock_addr.sa_family;
        throw SocketError("bind failed.");
    }

    sock_fd = socket(sock_addr.sa_family, SOCK_STREAM, 0);
    if (sock_fd < 0) {
        LOG_ERROR << " socket create failed ." << sock_addr.sa_data << strerror(errno);
        throw SocketError("socket create failed.");
    }

    ret = ::bind(sock_fd, &sock_addr, sizeof(sock_addr));
    if (ret < 0) {
        LOG_ERROR << sock_fd << " bind failed ." << sock_addr.sa_data << strerror(errno);
        throw SocketError("bind failed.");
    }

    ret = listen(sock_fd, MAX_PENDING_CONNECTIONS_NUM);
    if (ret < 0) {
        LOG_ERROR << sock_fd << " listen failed ." << sock_addr.sa_data << strerror(errno);
        throw SocketError("listen failed.");
    }

    auto f = [=]() {
        return (void*)(new T);
    };

    route_map_.insert(std::make_pair(sock_fd, f));

    Event e(sock_fd, this);
    e.set_read_callback<TCPServer>(&TCPServer::CreateConnection);

    if (sock_addr.sa_family == PF_UNIX) {
        LOG_INFO << "Listen event on " << sock_addr.sa_data << "successfully";
    }
    else if (sock_addr.sa_family == PF_INET) {
        struct sockaddr_in *in_addr = (struct sockaddr_in *) (&sock_addr);
        LOG_INFO << "Listen event on "
        << inet_ntoa(in_addr->sin_addr)
        << ":"
        << in_addr->sin_port
        << "successfully";
    }

}

void TCPServer::CreateConnection(int fd, int data) {

#if defined(DC_DEBUG)
    LOG_DEBUG << fd << "has" << data << "connections";
#endif

    struct sockaddr sock_addr;
    socklen_t sock_addr_len;

    for (int i = 0; i < data; ++i) {

        int coon_fd = accept(fd, &sock_addr, &sock_addr_len);
        TCPConnection *coon;

        string from_address;
        if (sock_addr.sa_family == PF_UNIX) {
            from_address += sock_addr.sa_data;
        }
        else {
            from_address += inet_ntoa(((struct sockaddr_in *) &sock_addr)->sin_addr);
            from_address += std::to_string(((struct sockaddr_in *) &sock_addr)->sin_port);
        }

        LOG_INFO << fd
        << "Incoming connection from "
        << from_address;

        coon = new TCPConnection(coon_fd,
                                 from_address,
                                 route_map_[fd]);

        dc::Event e(coon_fd, coon);
        e.set_read_callback<TCPConnection>(&TCPConnection::_ReadEvent);
        e.set_close_callback<TCPConnection>(&TCPConnection::_WriteEvent);
        dc::IOLoop::Current()->AddEvent(e);

        connection_poll_.insert(make_pair(coon_fd, coon));


    }

}

//void TCPServer::CloseConnection(int fd, int data) {
//#if defined(DC_DEBUG)
//    LOG_DEBUG << fd << "connection " << data << "connections";
//#endif
//
//
//}

}