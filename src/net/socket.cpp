#include "abathur/net/socket.hpp"

#include <cstring>

#include "abathur/net/inet_address.hpp"
#include "abathur/log.hpp"

const static int MAX_PENDING_CONNECTIONS_NUM = 200;

namespace abathur::net {

    Socket::Socket(std::shared_ptr<InetAddress> address) {
        address_ = address;
        fd_ = socket(address_->getProtocolFamily(), SOCK_STREAM, 0);
        if (fd_ < 0) {
            LOG_ERROR << " socket create failed" << address_->getAddrString() << strerror(errno);
        }
    }

    Socket::Socket(int fd, std::shared_ptr<InetAddress> address) {
        fd_ = fd;
        address_ = address;
    }
    int Socket::Bind() {
        int ret = ::bind(fd_, address_->getSockAddrPtr(), address_->getAddressLen());
        if (ret < 0) {
            LOG_ERROR << fd_ << " bind failed" << address_->getAddrString() << strerror(errno);
            return 2;
        }
        return 0;
    }

    int Socket::Send(const char* data, size_t size) {
        return send(fd_, data, size, 0);
    }

    int Socket::Recv(char* data, size_t size) {
        return ::recv(fd_, data, size, 0);
    }

    int Socket::Listen() {
        int ret = listen(fd_, MAX_PENDING_CONNECTIONS_NUM);
        if (ret < 0) {
            LOG_ERROR << fd_ << " listen failed" << address_->getAddrString() << strerror(errno);
            return 2;
        }
        return 0;

    }

    int Socket::GetFD() {
        return fd_;
    }

    std::shared_ptr<Socket> Socket::Accept() {

        sockaddr sock_addr;
        socklen_t sock_addr_len;
        int coon_fd = accept(fd_, &sock_addr, &sock_addr_len);
        if (coon_fd < 0) {
            return nullptr;
        }
        return std::shared_ptr<Socket>(new Socket(
                coon_fd,
                std::shared_ptr<InetAddress>(new InetAddress(&sock_addr, sock_addr_len))
        ));
    }

}
