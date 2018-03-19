#ifndef _ABATHUR_SOCKET_HPP_
#define _ABATHUR_SOCKET_HPP_

#include <iostream>
#include <memory>

#include "abathur/net/inet_address.hpp"

namespace abathur::util {
    class Buffer;
}

namespace abathur::net {

    class Socket {
    private:
        int fd_;
        InetAddress* address_ = nullptr;

        Socket(const Socket&) = delete;
        const Socket& operator=(const Socket&) = delete;
    public:
        Socket(InetAddress*);
        Socket(int fd, InetAddress*);

        int Bind();

        int Send(util::Buffer&);
        int Recv(util::Buffer&);

        int Listen();

        int Connect();

        int GetFD();

        Socket* Accept();

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
