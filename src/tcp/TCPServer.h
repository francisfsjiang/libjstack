//
// Created by Neveralso on 15/3/19.
//

#ifndef _DEMONIAC_TCPSERVER_H_
#define _DEMONIAC_TCPSERVER_H_

#include <map>
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "../IOLoop.h"
#include "../util/noncopyable.h"
#include "TCPConnection.h"
#include "../Log.h"
#include "../util/error.h"

namespace dc {

class TCPServer {
private:

    const int MAX_PENDING_CONNECTIONS_NUM = 200;

    std::map<int, std::function<void *()>> route_map_;

    std::map<int, TCPConnection *> connection_poll_;
public:
    TCPServer();

    template<typename T>
    void AddHandler(const sockaddr &sock_addr) {

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
            return (void *) (new T);
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

    void CreateConnection(int fd, int data);

};

}

#endif //_DEMONIAC_TCPSERVER_H_
