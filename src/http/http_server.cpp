#include "abathur/http/http_server.hpp"

#include "abathur/event.hpp"
#include "abathur/net/socket_server.hpp"

namespace abathur::http {
    HTTPServer::HTTPServer(net::InetAddress *address): abathur::net::SocketServer(address){
        LOG_TRACE << "HTTPServer constructing, " << this;

    }
    HTTPServer::~HTTPServer() {
        LOG_TRACE << "HTTPServer deconstructing, " << this;

    }

}