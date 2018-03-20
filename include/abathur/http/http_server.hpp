#ifndef _ABATHUR_HTTP_HTTP_SERVER_HPP_
#define _ABATHUR_HTTP_HTTP_SERVER_HPP_

#include "abathur/net/socket_server.hpp"

namespace abathur::net {
    class InetAddress;
}

namespace abathur::http {

    class HTTPHandler;

    class HTTPServer: public net::SocketServer {
    private:
    public:
        HTTPServer(net::InetAddress* address);
        ~HTTPServer();

        template<typename T>
        int set_handler() {

            if (!std::is_base_of<HTTPHandler, T>::value) {
                LOG_ERROR << "Wrong handler type" << typeid(T).name();
                return 2;
            }

            socket_handler_generator_ = [=](net::Socket* socket) {
                return dynamic_cast<HTTPHandler*>(new T(socket));
            };
            return 0;
        }
    };
}


#endif //_ABATHUR_HTTP_HTTP_SERVER_HPP_
