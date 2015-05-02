//
// Created by Neveralso on 15/3/19.
//

#ifndef _DEMONIAC_TCP_TCPCONNECTION_H_
#define _DEMONIAC_TCP_TCPCONNECTION_H_
#include <functional>
#include <queue>
#include <string>

#include "demoniac/util/event_handler.h"

namespace demoniac {
namespace tcp {


class TCPHandler;

class TCPServer;

class TCPConnection : public util::EventHandler {
private:
    int fd_;
    std::string from_address_ = "";
    TCPHandler *handler_ = nullptr;
    TCPServer *tcp_server_;
    std::queue<std::string> msg_queue_;

public:
    TCPConnection(const int &fd,
                  const std::string &from_address,
                  const std::function<void *()> &handler_generator,
                  TCPServer *tcp_server);

    void WriteMsg(const std::string &msg);

    void _ReadCallback(int fd, int data);

    void _WriteCallback(int fd, int data);

    void _CloseCallback(int fd, int data);

};


}
}

#endif //_DEMONIAC_TCPCONNECTION_H_
