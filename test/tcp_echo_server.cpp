#include <iostream>
#include <cstring>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "abathur/io_loop.hpp"
#include "abathur/net/socket_server.hpp"
#include "abathur/net/tcp_handler.hpp"

#define LISTEN_PORT 8002
#define LISTEN_ADDR "0.0.0.0"

class EchoHandler : abathur::net::TCPHandler {
private:
    const static int BUFFER_SIZE = 200;
    char buffer_[BUFFER_SIZE];
public:
    EchoHandler() : TCPHandler() {};
    std::string Recv(const std::string msg) {
        time_t te = time(NULL);
        strftime(buffer_, BUFFER_SIZE, "%m-%d-%Y %H:%M:%S  hi.", gmtime(&te));
        std::string s(buffer_);
        s+=msg;
        s+="\n";
        std::cout<<s<<endl;

        return s;
    }
};

int main() {

    char buf[50];
    getcwd(buf, sizeof(buf));
    std::cout<<buf<<endl;

    sockaddr_in in_addr;
    in_addr.sin_family = PF_INET;
    in_addr.sin_port = htons(LISTEN_PORT);
    in_addr.sin_addr.s_addr = htonl(inet_addr(LISTEN_ADDR));
    sockaddr sock_addr;
    memcpy(&sock_addr, &in_addr, sizeof(in_addr));
    abathur::net::TCPServer *tcp_server = new abathur::net::SocketServer();
    tcp_server->AddHandler<EchoHandler>(*((sockaddr*)&in_addr));
    abathur::IOLoop::Current()->Start();
    return 0;
}