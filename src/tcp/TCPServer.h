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
#include "../util/EventHandler.h"
#include "../util/error.h"

namespace dc {

class TCPServer : public EventHandler{
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

        auto f = [=]() {
            return (void *) (new T);
        };

        _AddHandler(sock_addr, f);
    }

private:
    virtual void _WriteCallback(int fd, int data);

    virtual void _CloseCallback(int fd, int data);

    void _AddHandler(const sockaddr &sock_addr, std::function<void *()>);

    void _ReadCallback(int fd, int data);

    void CreateConnection(int fd, int data);

};

}

#endif //_DEMONIAC_TCPSERVER_H_
