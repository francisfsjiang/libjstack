#include <iostream>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>

#include "abathur/abathur.hpp"
#include "abathur/http/http_handler.hpp"
#include "abathur/http/http_server.hpp"
#include "abathur/http/http_response.hpp"
#include "abathur/http/async_http_client.hpp"

#define LISTEN_PORT 8000
#define LISTEN_ADDR "::"


class ProxyHandler : public abathur::http::HTTPHandler{
    private:
    public:
        ProxyHandler() : abathur::http::HTTPHandler() {};
        abathur::http::HTTPResponse* handle_get(const abathur::http::HTTPRequest& request) override {

            auto new_resp = new abathur::http::HTTPResponse();

            auto s = std::string(request.get_body()->data_to_read(), request.get_body()->size());

            auto client = new abathur::http::AsyncHTTPClient();
            // Let magic begin
            auto req = abathur::http::HTTPRequest(s.data());

            auto resp = client->perform_request(req);
            std::cout << resp->get_body()->size() << std::endl;
            new_resp->write(resp->get_body()->data_to_read(), resp->get_body()->size());

            auto status_code = resp->status_code();
            std::cout << static_cast<unsigned int>(status_code) << std::endl;

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

int main(int, const char**) {

    abathur::net::InetAddress* addr;
    addr = new abathur::net::InetAddress(LISTEN_ADDR, LISTEN_PORT);
    std::cout << addr->to_string() << std::endl;

    auto http_server = new abathur::http::HTTPServer(addr);
    http_server->init();
    http_server->set_http_handler<ProxyHandler>("/");

    abathur::IOLoop::current()->start();
    return 0;
}
