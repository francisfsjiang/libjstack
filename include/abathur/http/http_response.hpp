#ifndef _ABATHUR_HTTP_HTTP_RESPONSE_HPP_
#define _ABATHUR_HTTP_HTTP_RESPONSE_HPP_

#include <string>

#include "abathur/http/http_request.hpp"

namespace abathur::util {
    class Buffer;
}

namespace abathur::http {

    class HTTPParser;

    class AsyncHTTPClient;

    class HTTPResponse{
        friend class AsyncHTTPClient;
    private:
        HTTP_VERSION version_;
        int status_code_;
        util::Buffer* body_;
        std::map<std::string, std::string>* header_;

    public:
        HTTPResponse();
        HTTPResponse(const HTTPResponse&);
        ~HTTPResponse();

        int status_code();
        util::Buffer* get_body();
        std::map<std::string, std::string>* get_header();
        void set_header(const std::string&, const std::string&);

        size_t write(const std::string&);
        size_t write(const char*, size_t);
        size_t write_to_buffer(util::Buffer& buffer);
    };
}


#endif //_ABATHUR_HTTP_HTTP_RESPONSE_HPP_
