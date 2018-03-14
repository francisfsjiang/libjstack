#include "abathur/net/socket.hpp"

#include <cstring>
#include <unistd.h>

#include <netinet/in.h>
#include <netinet/tcp.h>

#include <fcntl.h>

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
        int ret = ::recv(fd_, data, size, 0);
        LOG_TRACE << "Recv " << ret << " bytes.";
        return ret;
    }

    int Socket::Listen() {
        int ret = listen(fd_, MAX_PENDING_CONNECTIONS_NUM);
        if (ret < 0) {
            LOG_ERROR << fd_ << " listen failed" << address_->getAddrString() << strerror(errno);
            return 2;
        }
        return 0;

    }

    int Socket::Connect() {
        return ::connect(fd_, address_->getSockAddrPtr(), address_->getAddressLen());
    }

    int Socket::GetFD() {
        return fd_;
    }

    std::shared_ptr<Socket> Socket::Accept() {

        sockaddr sock_addr;
        socklen_t sock_addr_len;
        int coon_fd = accept(fd_, &sock_addr, &sock_addr_len);
        if (coon_fd < 0) {
            int savedErrno = errno;
            LOG_ERROR << "Socket::accept";
            switch (savedErrno)
            {
                case EAGAIN:
                case ECONNABORTED:
                case EINTR:
                case EPROTO: // ???
                case EPERM:
                case EMFILE: // per-process lmit of open file desctiptor ???
                    // expected errors
                    errno = savedErrno;
                    break;
                case EBADF:
                case EFAULT:
                case EINVAL:
                case ENFILE:
                case ENOBUFS:
                case ENOMEM:
                case ENOTSOCK:
                case EOPNOTSUPP:
                    // unexpected errors
                    LOG_FATAL << "unexpected error of ::accept " << savedErrno;
                    break;
                default:
                    LOG_FATAL << "unknown error of ::accept " << savedErrno;
                    break;
            }
            return nullptr;
        }
        return std::shared_ptr<Socket>(new Socket(
                coon_fd,
                std::shared_ptr<InetAddress>(new InetAddress(&sock_addr, sock_addr_len))
        ));
    }


    int Socket::Close()
    {
        LOG_TRACE << "socket " << fd_ << "closing";
        if (::close(fd_) < 0)
        {
            LOG_FATAL<< "sockets::close";
            return 2;
        }
        return 0;
    }

    int Socket::SetNonBlocking(bool) {
        // non-block
        int flags = ::fcntl(fd_, F_GETFL, 0);
        flags |= O_NONBLOCK;
        int ret = ::fcntl(fd_, F_SETFL, flags);
        if (ret < 0)
        {
            LOG_FATAL << "Set non blocking failed.";
            return 2;
        }
        return 0;
    }

    int Socket::SetCloseOnExec(bool) {
        // close-on-exec
        int flags = ::fcntl(fd_, F_GETFD, 0);
        flags |= FD_CLOEXEC;
        int ret = ::fcntl(fd_, F_SETFD, flags);
        if (ret < 0)
        {
            LOG_FATAL << "Set close on exec failed.";
            return 2;
        }
        return 0;
    }

    int Socket::SetTcpNoDelay(bool on)
    {
        int optval = on ? 1 : 0;
        ::setsockopt(fd_, IPPROTO_TCP, TCP_NODELAY,
                     &optval, static_cast<socklen_t>(sizeof optval));
        // FIXME CHECK
        return 0;
    }

    int Socket::SetReuseAddr(bool on)
    {
        int optval = on ? 1 : 0;
        int ret = ::setsockopt(fd_, SOL_SOCKET, SO_REUSEADDR,
                     &optval, static_cast<socklen_t>(sizeof optval));
        if (ret < 0 && on)
        {
            LOG_FATAL << "Set resuse addr failed.";
            return 2;
        }
        return 0;
    }

    int Socket::SetReusePort(bool on)
    {
#ifdef SO_REUSEPORT
        int optval = on ? 1 : 0;
        int ret = ::setsockopt(fd_, SOL_SOCKET, SO_REUSEPORT,
                               &optval, static_cast<socklen_t>(sizeof optval));
        if (ret < 0 && on)
        {
            LOG_FATAL << "SO_REUSEPORT failed.";
        }
#else
        if (on)
        {
            LOG_ERROR << "SO_REUSEPORT is not supported.";
        }
#endif
        return 0;
    }

    int Socket::SetKeepAlive(bool on)
    {
        int optval = on ? 1 : 0;
        int ret = ::setsockopt(fd_, SOL_SOCKET, SO_KEEPALIVE,
                     &optval, static_cast<socklen_t>(sizeof optval));
        if (ret < 0 && on)
        {
            LOG_FATAL << "Set keep alive failed.";
        }
        // FIXME CHECK
        return 0;
    }


    Socket::~Socket() {
        Close();
    }
}
