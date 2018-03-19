#ifndef _ABATHUR_HTTP_HTTP_RESPONSE_HPP_
#define _ABATHUR_HTTP_HTTP_RESPONSE_HPP_

#include <string>

#include "abathur/http/http_request.hpp"

namespace abathur::util {
    class Buffer;
}

namespace abathur::http {
    using namespace abathur::util;

    namespace parser {
            class HTTPParser;
    }

    class AsyncHTTPClient;

    class HTTPResponse{
        friend class AsyncHTTPClient;
    private:
        HTTP_VERSION version_;
        int status_code_;
        Buffer* body_;
        std::map<std::string, std::string>* header_;

    public:
        HTTPResponse();
        HTTPResponse(const HTTPResponse&);
        ~HTTPResponse();

        int status_code();
        Buffer* get_body();
        std::map<std::string, std::string>* get_header();

    };
}


#endif //_ABATHUR_HTTP_HTTP_RESPONSE_HPP_
