#ifndef _ABATHUR_HTTP_REQUEST_HPP_
#define _ABATHUR_HTTP_REQUEST_HPP_

#include <string>
#include <map>

#include "abathur/http/http_parser.hpp"

namespace abathur::util {
    class Buffer;
}

namespace abathur::http {

    class AsyncHTTPClient;

    class HTTPRequest{
        friend class AsyncHTTPClient;
        friend class HTTPParser;
    private:
        HTTP_METHOD method_;
        std::string host_;
        std::string url_;
        HTTP_VERSION version_;

        std::map<std::string, std::string>* header_;
        util::Buffer* post_buffer_;

    public:
        HTTPRequest();
        HTTPRequest(const std::string&);
        HTTPRequest(const std::string&, HTTP_METHOD);
        HTTPRequest(const HTTPRequest&);
        void prepare(const std::string&, HTTP_METHOD);
        ~HTTPRequest();

        int write_post_data(const char*, size_t);
        void set_header(const std::string&, const std::string&);
        void set_version(HTTP_VERSION);

    };
}


#endif //_ABATHUR_HTTP_REQUEST_HPP_
