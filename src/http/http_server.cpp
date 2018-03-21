#include "abathur/http/http_server.hpp"

#include "abathur/event.hpp"
#include "abathur/http/http_handler_wrapper.hpp"
#include "abathur/net/socket.hpp"
#include "abathur/net/socket_handler.hpp"

namespace abathur::http {
    using namespace abathur::net;

    HTTPServer::HTTPServer(net::InetAddress *address): abathur::net::SocketServer(address){
        LOG_TRACE << "HTTPServer constructing, " << this;
        set_handler<HTTPHandlerWrapper>();

        router_ = new RouterType();

    }
    HTTPServer::~HTTPServer() {
        LOG_TRACE << "HTTPServer deconstructing, " << this;

    }

    int HTTPServer::process_event(const Event &event) {
        init();

        LOG_TRACE << "SocketServer fd " << event.get_fd()<< " have incomming connections";


        while (true) {
            auto new_socket = socket_->accept();
            if (!new_socket) break;

            new_socket->set_non_blocking(true);
            SocketHandler* s = socket_handler_generator_(new_socket);
            s->init((void*)router_);
        }
        return 1;
    }
}