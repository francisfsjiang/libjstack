#ifndef _ABATHUR_HTTP_RESPONSE_HPP_
#define _ABATHUR_HTTP_RESPONSE_HPP_

#include <string>

namespace abathur::http {

    class AsyncHTTPClient;

    class HTTPResponse{
        friend class AsyncHTTPClient;
    private:
        int status_code_;
        std::string content_type_;
        std::string content_;
    public:
        HTTPResponse(int);
        ~HTTPResponse();

        int status_code();
        std::string content();

    };
}


#endif //_ABATHUR_HTTP_RESPONSE_HPP_
