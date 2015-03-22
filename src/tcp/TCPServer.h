//
// Created by Neveralso on 15/3/19.
//

#ifndef _DEMONIAC_TCPSERVER_H_
#define _DEMONIAC_TCPSERVER_H_

#include <map>
#include <iostream>
//#include <functional>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

#include "../IOLoop.h"
#include "../util/noncopyable.h"

namespace dc {

class TCPServer : noncopyable {
private:

    const int MAX_PENDING_CONNECTIONS_NUM = 200;

    std::map<int, std::function<void *()>> port_route_map;
public:
    template<typename T>
    void AddHandler(const struct sockaddr &sock_addr);

    void CreateConnection(int fd, int data);

};

}

#endif //_DEMONIAC_TCPSERVER_H_
