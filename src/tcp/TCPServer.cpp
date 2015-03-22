//
// Created by Neveralso on 15/3/19.
//

#include "TCPServer.h"

#include "../Log.h"
#include "../util/error.h"

namespace dc {

template<typename T>
void TCPServer::AddHandler(const struct sockaddr &sock_addr) {
    auto f = [=]() {
        return dynamic_cast<void *>(new T);
    };
    int sock_fd, ret;
    if (sock_addr.sa_family == PF_UNIX ||
            sock_addr.sa_family == PF_INET) {

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

        Event e(sock_fd, this);
        e.set_read_callback<TCPServer>(&TCPServer::CreateConnection);

        port_route_map.insert(std::make_pair(sock_fd, f));

    }
    else {
        LOG_ERROR << "target protocol supported";
        throw SocketError("bind failed.");
    }

}

void TCPServer::CreateConnection(int fd, int data) {
#if defined(DC_DEBUG)
    LOG_DEBUG << fd << "has" << data << "connections";
#endif

}

}