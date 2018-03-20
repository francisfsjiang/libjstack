#ifndef _ABATHUR_HTTP_HTTP_HANDLER_HPP_
#define _ABATHUR_HTTP_HTTP_HANDLER_HPP_

#include "abathur/net/socket_handler.hpp"

namespace abathur::net {
    class Socket;
}

namespace abathur::http {

    class HTTPResponse;
    class HTTPRequest;
    class HTTPParser;

    class HTTPHandler: public net::SocketHandler{
    private:
        HTTPParser* parser_;
        HTTPRequest* request_;
        HTTPResponse* response_;
    public:
        HTTPHandler(net::Socket*);
        virtual ~HTTPHandler();

        virtual int handle_socket_data(util::Buffer&);

        virtual HTTPResponse* handle_http_request(HTTPRequest&) = 0;
    };
}


#endif //_ABATHUR_HTTP_HANDLER_HPP_
