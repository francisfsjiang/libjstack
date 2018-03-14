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

        int Connect();

        int GetFD();

        std::shared_ptr<Socket> Accept();

        int Close();
        int SetNonBlocking(bool);
        int SetCloseOnExec(bool);
        int SetTcpNoDelay(bool);
        int SetReuseAddr(bool);
        int SetReusePort(bool);
        int SetKeepAlive(bool);

        ~Socket();

    };
}


#endif //_ABATHUR_SOCKET_HPP_
