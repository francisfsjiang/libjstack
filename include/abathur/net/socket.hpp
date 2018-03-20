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

        int bind();

        int send(util::Buffer &);
        int recv(util::Buffer &);

        int listen();

        int connect();

        int get_fd();

        Socket* accept();

        int close();
        int set_non_blocking(bool);
        int set_close_on_exec(bool);
        int set_tcp_no_delay(bool);
        int set_reuse_addr(bool);
        int set_reuse_port(bool);
        int set_keep_alive(bool);

        ~Socket();

    };
}


#endif //_ABATHUR_SOCKET_HPP_
