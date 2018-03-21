#include <iostream>

#include "abathur/abathur.hpp"

#define LISTEN_PORT 8000
#define LISTEN_ADDR "::"


class HTTPEchoHandler : public abathur::http::HTTPHandler{
    public:
        HTTPEchoHandler() : abathur::http::HTTPHandler() {};
        abathur::http::HTTPResponse* handle_get(const abathur::http::HTTPRequest& request) override {

            auto resp = new abathur::http::HTTPResponse();
            auto s = std::string(
                    request.get_body()->data_to_read(),
                    request.get_body()->size()
            );
            resp->write(s);
            finish();

            return resp;
        }
};


int main(int , const char**) {

    abathur::net::InetAddress* addr;
    addr = new abathur::net::InetAddress(LISTEN_ADDR, LISTEN_PORT);

    std::cout << addr->to_string() << std::endl;

    auto http_server = new abathur::http::HTTPServer(addr);
    http_server->init();
    http_server->set_http_handler<HTTPEchoHandler>("/");

    abathur::IOLoop::current()->start();
    return 0;
}
