#ifndef _ABATHUR_SOCKET_HPP_
#define _ABATHUR_SOCKET_HPP_

#include <iostream>
#include <memory>

#include "abathur/net/inet_address.hpp"

namespace abathur::net {

    class Socket {
    private:
        int fd_;
        std::shared_ptr<InetAddress> address_ = nullptr;

        Socket(const Socket&) = delete;
        const Socket& operator=(const Socket&) = delete;
    public:
        Socket(std::shared_ptr<InetAddress>);
        Socket(int fd, std::shared_ptr<InetAddress>);

        int Bind();

        int Send(const char*, size_t);
        int Recv(char*, size_t);

        int Listen();

        int GetFD();

        std::shared_ptr<Socket> Accept();

    };
}


#endif //_ABATHUR_SOCKET_HPP_
