#include <iostream>
#include <string>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "../src/IOLoop.h"
#include "../src/tcp/TCPServer.h"
#include "../src/tcp/TCPHandler.h"

#define LISTEN_PORT 8000
#define LISTEN_ADDR "0.0.0.0"

class EchoHandler : dc::TCPHandler {
public:
    std::string Recv(const std::string msg) {
        std::string s("Hi ");
        s += msg;
        std::cout << "Send to " << from_ << ":" << s << std::endl;
        return s;
    }
};

int main() {
    sockaddr_in in_addr;
    in_addr.sin_family = PF_INET;
    in_addr.sin_port = htons(LISTEN_PORT);
    in_addr.sin_addr.s_addr = htonl(inet_addr(LISTEN_ADDR));

    dc::TCPServer *tcp_server = new dc::TCPServer();
    tcp_server->AddHandler<EchoHandler>(*((sockaddr *) &in_addr));

    dc::IOLoop::Current()->Loop();
    return 0;
}
