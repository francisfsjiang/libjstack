#include <iostream>
#include <cstring>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "abathur/abathur.hpp"
#include "abathur/http/async_http_client.hpp"

#define LISTEN_PORT 8080
#define LISTEN_ADDR "::"


class EchoHandler : public abathur::net::SocketHandler{
    private:
    public:
        explicit EchoHandler(abathur::net::Socket* socket) : abathur::net::SocketHandler(socket) {};
        virtual int Process(abathur::util::Buffer& buffer) override {

            auto s = std::string(buffer.data(), buffer.size());

            auto client = new abathur::http::AsyncHTTPClient();
//            auto req = abathur::http::HTTPRequest("www.baidu.com");
//            auto req = abathur::http::HTTPRequest("www.qq.com");
//            auto req = abathur::http::HTTPRequest("www.stroustrup.com");
            auto req = abathur::http::HTTPRequest("127.0.0.1");

            auto resp = client->perform_request(req);
            std::cout << resp->get_body()->data_to_read() << std::endl;

            auto status_code = resp->status_code();
            std::cout << status_code << std::endl;

            auto header = resp->get_header();
            for(auto h: *header) {
                std::cout << h.first << " ---- " << h.second <<std::endl;
            }
            delete header;

            delete resp;

            delete client;

            Write(s.data(), s.size());
            finish();

            return static_cast<int>(buffer.size());
        }
};

int main(int argc, const char* argv[]) {

    char buf[50];
    getcwd(buf, sizeof(buf));
    std::cout<<buf<< std::endl;

    abathur::net::InetAddress* addr;
    if (argc > 1) {
        addr = new abathur::net::InetAddress(LISTEN_ADDR, atoi(argv[1]));
    }
    else {
        addr = new abathur::net::InetAddress(LISTEN_ADDR, LISTEN_PORT);
    }
    std::cout << addr->getAddrString() << ":" << addr->getPort() << std::endl;

    abathur::net::SocketServer* tcp_server = new abathur::net::SocketServer(addr);
    tcp_server->Init();
    tcp_server->SetHandler<EchoHandler>();

    abathur::IOLoop::Current()->Start();
    return 0;
}
