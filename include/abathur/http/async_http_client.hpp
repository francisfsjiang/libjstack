#ifndef _ABATHUR_ASYNC_HTTP_CLIENT_HPP_
#define _ABATHUR_ASYNC_HTTP_CLIENT_HPP_

#include <memory>
#include <vector>

#include "abathur/event_processor.hpp"

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

    class AsyncHTTPClient: EventProcessor {
    private:
        CURLM* curl_m_handle_;
        CURL* curl_handle_;
        int curl_socket_;
        bool done_;

        HTTPResponse* response_ = nullptr;
//        std::shared_ptr<util::Timer> curl_timeout_timer_ = nullptr;
        std::shared_ptr<Channel> in_channel_ = nullptr;
        std::vector<std::shared_ptr<util::Timer>>* timers_ = nullptr;

        void prepare_request(const HTTPRequest&);
        void prepare_response();

        int check_multi_info();

        static int handle_body_write(void*, size_t size, size_t, HTTPResponse* resp);
        static int handle_header_write(char*, size_t, size_t, HTTPResponse* resp);
        static int handle_socket(CURL *easy, curl_socket_t s, int action, AsyncHTTPClient* userp, void *socketp);
        static int start_timeout(CURLM *multi, long timeout_ms, AsyncHTTPClient* userp);

    public:

        AsyncHTTPClient();
        ~AsyncHTTPClient();

        HTTPResponse* perform_request(const HTTPRequest&);
        int process_event(const Event &event) override;

    };
}


#endif //_ABATHUR_ASYNC_HTTP_CLIENT_H_
