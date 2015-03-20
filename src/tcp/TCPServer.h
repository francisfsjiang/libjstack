//
// Created by Neveralso on 15/3/19.
//

#ifndef _DEMONIAC_TCPSERVER_H_
#define _DEMONIAC_TCPSERVER_H_

#include <map>
#include <functional>
#include <sys/socket.h>

#include "IOLoop.h"
#include "TCPHandler.h"
#include "util/noncopyable.h"

namespace dc {

class TCPServer : noncopyable {
private:
    std::map<int, std::function<void*()>> port_route_map;
public:
    template<typename T>
    void AddHandler(sa_family_t sock_type, sockaddr* sock_addr);

    void AddListenEvent(sa_family_t sock_type, sockaddr* sock_addr);
};

}

#endif //_DEMONIAC_TCPSERVER_H_
