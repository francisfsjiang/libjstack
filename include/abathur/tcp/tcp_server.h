#ifndef _ABATHUR_TCP_TCPSERVER_H_
#define _ABATHUR_TCP_TCPSERVER_H_

#include <functional>
#include <map>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "abathur/util/error.h"
#include "abathur/log.h"

namespace abathur {
namespace tcp {


class IOLoop;

class TCPConnection;

class TCPHandler;

class TCPServer {
private:

    const static int MAX_PENDING_CONNECTIONS_NUM = 200;

    std::map<int, std::function<void *()>> route_map_;

    std::map<int, TCPConnection *> connection_poll_;

    TCPServer(const TCPServer&) = delete;
    const TCPServer& operator=(const TCPServer&) = delete;

public:
    TCPServer() = default;

    template<typename T>
    void AddHandler(const sockaddr &sock_addr) {

        if (!std::is_base_of<TCPHandler, T>::value) {
            LOG_ERROR << "Wrong handler type" << typeid(T).name();
            throw util::HandlerTypeError(typeid(T).name());
        }

        auto f = [=]() {
            return (void *) (new T);
        };

        _AddHandler(sock_addr, f);
    }

//    virtual void _WriteCallback(int fd, int data);
//
//    virtual void _CloseCallback(int fd, int data);
//
//    virtual void _ReadCallback(int fd, int data);

    void _AddHandler(const sockaddr &sock_addr, std::function<void *()>);

    void CreateConnection(int fd, int data);

    void RemoveConnection(int fd);

};


}
}

#endif //_ABATHUR_TCPSERVER_H_
