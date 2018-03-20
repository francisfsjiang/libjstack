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
    Socket* socket_ptr_ = nullptr;
    bool wait_for_write_event_ = false;
    bool finished_ = false;

protected:
    abathur::util::Buffer read_buffer_, write_buffer_;

public:
    SocketHandler(Socket*);
    virtual ~SocketHandler();

    virtual int Init();

    int process_event(const Event &) override ;

    int write(const char *, size_t);

    virtual int handle_socket_data(util::Buffer&) = 0;

    void finish();
};


}

#endif //_ABATHUR_SOCKET_HANDLER_HPP_
