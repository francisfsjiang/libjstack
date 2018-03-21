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
        HTTPVersion version_;

        std::map<std::string, std::string>* header_;
        util::Buffer* body_;

    public:
        HTTPRequest();
        HTTPRequest(const std::string&);
        HTTPRequest(const std::string&, HTTP_METHOD);
        HTTPRequest(const HTTPRequest&);
        ~HTTPRequest();

        void prepare(const std::string&, HTTP_METHOD);

        int write_post_data(const char*, size_t);
        const util::Buffer* get_body() const;
        void set_header(const std::string&, const std::string&);
        void set_version(HTTPVersion);

        HTTP_METHOD get_method() const;
        std::string get_url() const;

    };
}


#endif //_ABATHUR_HTTP_REQUEST_HPP_
