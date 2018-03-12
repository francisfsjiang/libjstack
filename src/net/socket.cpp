#include "abathur/net/socket.hpp"

#include "abathur/net/inet_address.hpp"

const static int MAX_PENDING_CONNECTIONS_NUM = 200;

namespace abathur::net {

    Socket::Socket(const InetAddress& address) {
        fd_ = socket(address.getProtocolFamily(), SOCK_STREAM, 0);
        if (fd_ < 0) {
            LOG_ERROR << " socket create failed" << sock_addr.sa_data << strerror(errno);
        }
    }

    int Socket::Bind() {
        ret = ::bind(fd_, &sock_addr, sizeof(sock_addr));
        if (ret < 0) {
            LOG_ERROR << fd_ << " bind failed" << sock_addr.sa_data << strerror(errno);
        }
    }

    int Socket::Send(const char* data, size_t size) {
        send(fd_, data, size, 0);
    }

    int Socket::Listen() {
        ret = listen(fd_, MAX_PENDING_CONNECTIONS_NUM);
        if (ret < 0) {
            LOG_ERROR << fd_ << " listen failed" << sock_addr.sa_data << strerror(errno);
        }

    }

    int GetFD() {
        return fd_;
    }

    std::shared_ptr<Socket> Accept() {

        sockaddr sock_addr;
        socklen_t sock_addr_len;
        coon_fd = accept(fd, &sock_addr, &sock_addr_len);
        if (coon_fd < 0) {
            return nullptr;
        }
        return std::shared_ptr<Socket>(new Socket(coonfd, InetAddress(&sock_addr, sock_addr_len)));
    }

}
