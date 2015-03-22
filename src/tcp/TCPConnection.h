//
// Created by Neveralso on 15/3/19.
//

#ifndef _DEMONIAC_TCPCONNECTION_H_
#define _DEMONIAC_TCPCONNECTION_H_

#include <string>
#include <functional>
#include <queue>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>


#include "TCPHandler.h"

namespace dc {

class TCPConnection {
private:
    int fd_;
    std::string from_address_ = "";
    TCPHandler *handler_ = NULL;
    std::queue<std::string> msg_queue;

public:
    TCPConnection(const int& fd,
                  const std::string& from_address,
                  const std::function<void *()> handler_generator);

    void _ReadEvent(int fd, int data);

    void _WriteMsg(const std::string& msg);

    void _WriteEvent(int fd, int data);
};

}

#endif //_DEMONIAC_TCPCONNECTION_H_
