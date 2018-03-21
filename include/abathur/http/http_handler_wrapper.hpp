#ifndef _ABATHUR_HTTP_HTTP_HANDLER_WRAPPER_HPP_
#define _ABATHUR_HTTP_HTTP_HANDLER_WRAPPER_HPP_

#include <regex>
#include <vector>

#include "abathur/net/socket_handler.hpp"

namespace abathur::net {
    class Socket;
}

namespace abathur::http {

    class HTTPResponse;
    class HTTPRequest;
    class HTTPParser;
    class HTTPHandler;

    typedef std::vector<std::pair<std::regex, std::function<HTTPHandler*()>>> RouterType ;

    class HTTPHandlerWrapper: public net::SocketHandler{
    private:
        HTTPParser* parser_;

        RouterType* router_;

    public:
        HTTPHandlerWrapper(net::Socket*);
        virtual ~HTTPHandlerWrapper() override ;

        virtual int init(void*) override ;

        virtual size_t handle_socket_data(util::Buffer&) override ;

        HTTPResponse* dispatch_request(const HTTPRequest&);

    };
}


#endif //_ABATHUR_HTTP_HANDLER_WRAPPER_HPP_
