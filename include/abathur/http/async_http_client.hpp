#ifndef _ABATHUR_ASYNC_HTTP_CLIENT_HPP_
#define _ABATHUR_ASYNC_HTTP_CLIENT_HPP_

#include "abathur/event_processor.hpp"

#include "curl/curl.h"

namespace abathur::util {
    class Buffer;
}

namespace abathur::http {

    class HTTPRequest;
    class HTTPResponse;

    class AsyncHTTPClient: public EventProcessor {
    private:
        CURLM* curl_handle_;
        int curl_socket_;

        int handle_socket(CURL*, curl_socket_t, int, void*, void*);

        util::Buffer* recv_buffer_ = nullptr;
    public:
        AsyncHTTPClient();
        ~AsyncHTTPClient();

        HTTPResponse perform_request(const HTTPRequest&);

        void prepare_request(const HTTPRequest&);
        HTTPResponse prepare_response();

        int check_multi_info();
    };
}


#endif //_ABATHUR_ASYNC_HTTP_CLIENT_H_
