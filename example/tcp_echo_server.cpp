#include <iostream>

#include "abathur/abathur.hpp"

#define LISTEN_PORT 8000
#define LISTEN_ADDR "::"


class EchoHandler : public abathur::net::SocketHandler{
public:
    explicit EchoHandler(abathur::net::Socket* socket) : abathur::net::SocketHandler(socket) {};
    size_t handle_socket_data(abathur::util::Buffer &buffer) override {

        std::string str (buffer.data(), buffer.size());
        str += "Hello from Abathur, UTC ";
        str += abathur::util::get_datetime();
        std::cout<< str<< std::endl;

        write(str.data(), str.size());

        return static_cast<int>(buffer.size());
    }
};

int main(int, const char**) {

    auto addr = new abathur::net::InetAddress(LISTEN_ADDR, LISTEN_PORT);
    std::cout << addr->get_address_string() << ":" << addr->get_port() << std::endl;

    abathur::net::SocketServer* tcp_server = new abathur::net::SocketServer(addr);
    tcp_server->init();
    tcp_server->set_handler<EchoHandler>();

    abathur::IOLoop::current()->start();
    return 0;
}
