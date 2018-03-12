#ifndef _ABATHUR_TCP_SOCKET_HANDLER_HPP_
#define _ABATHUR_TCP_SOCKET_HANDLER_HPP_
#include <functional>
#include <queue>
#include <string>

#include "abathur/event_processor.hpp"


namespace abathur::net {


class TCPHandler;

class SocketServer;

class Socket;

class SocketHandler: public EventProcessor {
private:
    std::shared_ptr<Socket> socket_ptr_ = nullptr;

public:
    SocketHandler(std::shared_ptr<Socket>);

    void ProcessEvent(const Event &) override ;

    void WriteMsg(const std::string&);

};


}

#endif //_ABATHUR_SOCKET_HANDLER_HPP_
