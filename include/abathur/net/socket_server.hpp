#ifndef _ABATHUR_TCP_SOCKET_SERVER_HPP_
#define _ABATHUR_TCP_SOCKET_SERVER_HPP_

#include <functional>
#include <map>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "abathur/error.hpp"
#include "abathur/log.hpp"
#include "abathur/event_processor.hpp"

namespace abathur::net {

class IOLoop;
class Socket;
class SocketHandler;
class InetAddress;

class SocketServer: EventProcessor {
private:

    SocketServer(const SocketServer&) = delete;
    const SocketServer& operator=(const SocketServer&) = delete;

    std::shared_ptr<Socket> socket_ = nullptr;

    std::function<SocketHandler*(std::shared_ptr<Socket>)>socket_handler_generator_ = nullptr;

public:
    SocketServer(std::shared_ptr<InetAddress> address);

    void ProcessEvent(const Event&) override;

    template<typename T>
    int SetHandler() {

        if (!std::is_base_of<SocketHandler, T>::value) {
            LOG_ERROR << "Wrong handler type" << typeid(T).name();
            return 2;
        }

        socket_handler_generator_ = [=](std::shared_ptr<Socket> socket) {
            return (SocketHandler *) (new T(socket));
        };
        return 0;
    }

    void CreateConnection(int fd, int data);

};


}

#endif //_ABATHUR_SOCKET_SERVER_HPP_
