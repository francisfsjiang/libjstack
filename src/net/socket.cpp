#include "abathur/net/socket.hpp"

#include <cstring>
#include <unistd.h>

#include <netinet/in.h>
#include <netinet/tcp.h>

#include <fcntl.h>

#include "abathur/net/inet_address.hpp"
#include "abathur/util/buffer.hpp"
#include "abathur/log.hpp"

const static int MAX_PENDING_CONNECTIONS_NUM = 200;

namespace abathur::net {

    Socket::Socket(InetAddress* address) {
        LOG_TRACE << "Socket constructing , " << this;
        address_ = address;
        fd_ = socket(address_->getProtocolFamily(), SOCK_STREAM, 0);
        if (fd_ < 0) {
            LOG_ERROR << " socket create failed" << address_->getAddrString() << strerror(errno);
        }
    }

    Socket::Socket(int fd, InetAddress* address) {
        LOG_TRACE << "Socket constructing , " << this;
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

    int Socket::Send(util::Buffer& buffer) {
        ssize_t ret = send(fd_, buffer.data_to_read(), buffer.size(), 0);
        if(ret > 0) {
            buffer.set_reader_pos(buffer.get_reader_pos() + ret);
            buffer.shrink();
            return static_cast<int>(ret);
        }
        else {
            return -2;
        }
    }

    int Socket::Recv(util::Buffer& buffer) {
        ssize_t total_received = 0;
        while (true) {
            ssize_t ret = ::recv(fd_, buffer.data_to_write(), buffer.writeable_len(), 0);
            if(ret > 0) {
                buffer.set_writer_pos(buffer.get_writer_pos() + ret);
                if(buffer.size() == buffer.capacity()) {
                    buffer.resize();
                }
                total_received += ret;
                continue;
            }
            else {
                LOG_ERROR << "Recv failed, ret " << ret << " , " << strerror(errno);
                break;
            }
        }
        if(total_received > 0) {
            return static_cast<int>(total_received);
        }
        else {
            LOG_ERROR << "Recv failed, ret " << total_received << " , " << strerror(errno);
            return -2;
        }
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

    Socket* Socket::Accept() {

        sockaddr sock_addr;
        socklen_t sock_addr_len;
        int coon_fd = accept(fd_, &sock_addr, &sock_addr_len);
        if (coon_fd < 0) {
            int savedErrno = errno;
            LOG_TRACE << "Socket accept failed, reason " << strerror(savedErrno);
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
        return new Socket(
                coon_fd,
                new InetAddress(&sock_addr, sock_addr_len)
        );
    }


    int Socket::Close()
    {
        LOG_TRACE << "Socket " << fd_ << " closing";
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
        int ret = ::setsockopt(fd_, IPPROTO_TCP, TCP_NODELAY,
                     &optval, static_cast<socklen_t>(sizeof optval));
        if (ret < 0 && on)
        {
            LOG_FATAL << "Set tcp no-delay failed.";
            return 2;
        }
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
        return 0;
    }


    Socket::~Socket() {
        LOG_TRACE << "Socket deconstructing , " << this;
        Close();
    }
}
