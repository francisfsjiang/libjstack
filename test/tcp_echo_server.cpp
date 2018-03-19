#include <iostream>
#include <cstring>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "abathur/abathur.hpp"

#define LISTEN_PORT 8024
#define LISTEN_ADDR "::"


class EchoHandler : public abathur::net::SocketHandler{
    private:
        const static int BUFFER_SIZE = 200;
        char buffer_[BUFFER_SIZE];
    public:
        explicit EchoHandler(abathur::net::Socket* socket) : abathur::net::SocketHandler(socket) {};
        virtual int Process(abathur::util::Buffer& buffer) override {
            time_t te = time(NULL);
            strftime(buffer_, BUFFER_SIZE, "%m-%d-%Y %H:%M:%S  hi.", gmtime(&te));
            std::string s(buffer_);
            s+=std::string(buffer.data(), buffer.size());
            std::cout<<std::endl<<s<<std::endl;

            Write(s.data(), s.size());

            return static_cast<int>(buffer.size());
        }
};

int main(int, const char* []) {

    char buf[50];
    getcwd(buf, sizeof(buf));
    std::cout<<buf<< std::endl;

    auto addr = new abathur::net::InetAddress(LISTEN_ADDR, LISTEN_PORT);
    std::cout << addr->getAddrString() << ":" << addr->getPort() << std::endl;

    abathur::net::SocketServer* tcp_server = new abathur::net::SocketServer(addr);
    tcp_server->Init();
    tcp_server->SetHandler<EchoHandler>();

    abathur::IOLoop::Current()->Start();
    return 0;
}
