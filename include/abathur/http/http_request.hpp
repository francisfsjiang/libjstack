#ifndef _ABATHUR_HTTP_REQUEST_HPP_
#define _ABATHUR_HTTP_REQUEST_HPP_

#include <string>
#include <map>

#include <curl/curl.h>

namespace abathur::util {
    class Buffer;
}

namespace abathur::http {

    class AsyncHTTPClient;

    enum HTTP_METHOD {
        GET,
        POST,
        DELETE,
        PUT
    };

    enum HTTP_VERSION {
        HTTPNone= CURL_HTTP_VERSION_NONE,
        HTTP1_0 = CURL_HTTP_VERSION_1_0,
        HTTP1_1 = CURL_HTTP_VERSION_1_1,
        HTTP2_0   = CURL_HTTP_VERSION_2_0,
    };

    class HTTPRequest{
        friend class AsyncHTTPClient;
    private:
        HTTP_METHOD method_;
        std::string host_;
        std::map<std::string, std::string> header_;
        HTTP_VERSION version_;
        util::Buffer* post_buffer_ = nullptr;
    public:
        HTTPRequest(const std::string&);
        HTTPRequest(const std::string&, HTTP_METHOD);
        void prepare(const std::string&, HTTP_METHOD);
        ~HTTPRequest();

        int set_post_data(const char*, size_t);
        void set_header(const std::string&, const std::string&);
        void set_version(HTTP_VERSION);

    };
}


#endif //_ABATHUR_HTTP_REQUEST_HPP_
