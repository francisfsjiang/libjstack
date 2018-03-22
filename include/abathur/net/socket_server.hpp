#ifndef _ABATHUR_TCP_SOCKET_SERVER_HPP_
#define _ABATHUR_TCP_SOCKET_SERVER_HPP_

#include <functional>
#include <map>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "abathur/log.hpp"
#include "abathur/event_processor.hpp"

namespace abathur {
    class IOLoop;
}

namespace abathur::net {

class Socket;
class SocketHandler;
class InetAddress;

class SocketServer: public EventProcessor {
private:
    SocketServer(const SocketServer&) = delete;
    const SocketServer& operator=(const SocketServer&) = delete;

    bool inited_ = false;

protected:
    std::function<SocketHandler* (Socket*)>socket_handler_generator_ = nullptr;

    Socket* socket_ = nullptr;

public:
    SocketServer(InetAddress* address);

    ~SocketServer();

    template<typename T>
    int set_handler() {

        if (!std::is_base_of<SocketHandler, T>::value) {
            LOG_ERROR << "Wrong handler type" << typeid(T).name();
            return 2;
        }

        socket_handler_generator_ = [=](Socket* socket) {
            return dynamic_cast<SocketHandler*>(new T(socket));
        };
        return 0;
    }

    void create_connection(int fd, int data);

    int init();

    virtual int process_event(const Event &) override;
};


}

#endif //_ABATHUR_SOCKET_SERVER_HPP_
