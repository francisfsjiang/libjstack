#ifndef _ABATHUR_SOCKET_HPP_
#define _ABATHUR_SOCKET_HPP_

namespace abathur::net {

    class InetAddress;

    class Socket {
    private:
        int fd_;

        Socket(const Socket&) = delete;
        const Socket& operator=(const Socket&) = delete;
    public:
        Socket(const InetAddress&);
        Socket(int fd, const InetAddress&);

        int Bind();

        int Send(const char*, size_t);

        int Listen();

        int GetFD();

        std::shared_ptr<Socket> Accept();

    };
}


#endif //_ABATHUR_SOCKET_HPP_
