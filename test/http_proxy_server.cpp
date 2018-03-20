#include <iostream>
#include <cstring>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "abathur/abathur.hpp"
#include "abathur/http/http_handler.hpp"
#include "abathur/http/http_server.hpp"
#include "abathur/http/http_response.hpp"
#include "abathur/http/async_http_client.hpp"

#define LISTEN_PORT 8107
#define LISTEN_ADDR "::"


class EchoHandler : public abathur::http::HTTPHandler{
    private:
    public:
        explicit EchoHandler(abathur::net::Socket* socket) : abathur::http::HTTPHandler(socket) {};
        abathur::http::HTTPResponse* handle_http_request(abathur::http::HTTPRequest& request) override {

            auto new_resp = new abathur::http::HTTPResponse();

//            auto s = std::string(buffer.data(), buffer.size());

            auto client = new abathur::http::AsyncHTTPClient();
            auto req = abathur::http::HTTPRequest("www.baidu.com");
////            auto req = abathur::http::HTTPRequest("www.qq.com");
////            auto req = abathur::http::HTTPRequest("www.stroustrup.com");
//            auto req = abathur::http::HTTPRequest("127.0.0.1");

            auto resp = client->perform_request(req);
            std::cout << resp->get_body()->data_to_read() << std::endl;
            std::cout << resp->get_body()->size() << std::endl;
            new_resp->write(resp->get_body()->data_to_read(), resp->get_body()->size());

            auto status_code = resp->status_code();
            std::cout << status_code << std::endl;

            auto header = resp->get_header();
            for(auto h: *header) {
                std::cout << h.first << " ---- " << h.second <<std::endl;
            }
            delete header;

            delete resp;

            delete client;

            finish();

            return new_resp;
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
    std::cout << addr->to_string() << std::endl;

    auto http_server = new abathur::http::HTTPServer(addr);
    http_server->init();
    http_server->set_handler<EchoHandler>();

    abathur::IOLoop::current()->start();
    return 0;
}
