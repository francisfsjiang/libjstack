#ifndef _ABATHUR_ASYNC_HTTP_CLIENT_HPP_
#define _ABATHUR_ASYNC_HTTP_CLIENT_HPP_

#include "abathur/http/http_request.hpp"
#include "abathur/http/http_response.hpp"

#include "curl/curl.h"

namespace abathur {
    class Channel;
}

namespace abathur::util {
    class Buffer;
    class Timer;
}

namespace abathur::http {

    class HTTPRequest;
    class HTTPResponse;

    class AsyncHTTPClient {
    private:
        CURLM* curl_m_handle_;
        CURL* curl_handle_;
        int curl_socket_;

        HTTPResponse* response_ = nullptr;
        util::Timer* curl_timeout_timer_ = nullptr;
        std::shared_ptr<Channel> in_channel_ = nullptr;

        void prepare_request(const HTTPRequest&);
        HTTPResponse* prepare_response();

        int check_multi_info();

        static int handle_body_write(void*, size_t size, size_t, HTTPResponse* resp);
        static int handle_header_write(char*, size_t, size_t, HTTPResponse* resp);
        static int handle_socket(CURL *easy, curl_socket_t s, int action, AsyncHTTPClient* userp, void *socketp);
        static int start_timeout(CURLM *multi, long timeout_ms, AsyncHTTPClient* userp);

    public:

        AsyncHTTPClient();
        ~AsyncHTTPClient();

        HTTPResponse* perform_request(const HTTPRequest&);

    };
}


#endif //_ABATHUR_ASYNC_HTTP_CLIENT_H_
