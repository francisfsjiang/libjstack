#include <iostream>

#include "abathur/abathur.hpp"

#define LISTEN_PORT 8000
#define LISTEN_ADDR "::"

using namespace abathur;
using namespace abathur::net;
using namespace abathur::http;

class HTTPEchoHandler : public HTTPHandler{
public:
    HTTPEchoHandler() : HTTPHandler() {};
    HTTPResponse* handle_get(const HTTPRequest& request) override {

        auto resp = new HTTPResponse();
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

    InetAddress* addr;
    addr = new InetAddress(LISTEN_ADDR, LISTEN_PORT);

    std::cout << addr->to_string() << std::endl;

    auto http_server = new HTTPServer(addr);
    http_server->init();
    http_server->set_http_handler<HTTPEchoHandler>("/");

    IOLoop::current()->start();
    return 0;
}