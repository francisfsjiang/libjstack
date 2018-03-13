#ifndef _ABATHUR_TCP_SOCKET_HANDLER_HPP_
#define _ABATHUR_TCP_SOCKET_HANDLER_HPP_

#include <functional>
#include <queue>
#include <string>
#include <memory>


#include "abathur/util/buffer.hpp"
#include "abathur/event_processor.hpp"

namespace abathur::net {


class TCPHandler;

class SocketServer;

class Socket;


class SocketHandler: public EventProcessor {
private:
    std::shared_ptr<Socket> socket_ptr_ = nullptr;

    abathur::util::Buffer read_buffer_, write_buffer_;


public:
    SocketHandler(std::shared_ptr<Socket>);

    void ProcessEvent(const Event &) override ;

    int Write(const char*, size_t);

    virtual void Process(const char*, size_t) = 0;

};


}

#endif //_ABATHUR_SOCKET_HANDLER_HPP_
