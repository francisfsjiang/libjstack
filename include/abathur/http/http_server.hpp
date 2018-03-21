#ifndef _ABATHUR_HTTP_HTTP_SERVER_HPP_
#define _ABATHUR_HTTP_HTTP_SERVER_HPP_

#include <regex>
#include <vector>

#include "abathur/net/socket_server.hpp"

namespace abathur::net {
    class InetAddress;
}

namespace abathur::http {

    class HTTPHandlerWrapper;
    class HTTPHandler;

    typedef std::vector<std::pair<std::regex, std::function<HTTPHandler*()>>> RouterType ;

    class HTTPServer: public net::SocketServer {
    private:
        RouterType* router_;
    public:
        HTTPServer(net::InetAddress* address);
        ~HTTPServer();

        template<typename T>
        int set_http_handler(std::string path_regex_) {

            if (!std::is_base_of<HTTPHandler, T>::value) {
                LOG_ERROR << "Wrong handler type" << typeid(T).name();
                return 2;
            }

            router_->push_back(std::make_pair(
                    std::regex(path_regex_),
                    [=]() {
                        return dynamic_cast<HTTPHandler*>(new T());
                    }
            ));
            return 0;
        }

        int process_event(const Event &) override;
    };
}


#endif //_ABATHUR_HTTP_HTTP_SERVER_HPP_
