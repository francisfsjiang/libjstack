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

namespace dc {

class TCPServer {
private:

    const int MAX_PENDING_CONNECTIONS_NUM = 200;

    std::map<int, std::function<void *()>> route_map_;

    std::map<int, TCPConnection *> connection_poll_;
public:
    TCPServer();

    template<typename T>
    void AddHandler(const sockaddr &sock_addr);

    void CreateConnection(int fd, int data);

};

}

#endif //_DEMONIAC_TCPSERVER_H_
