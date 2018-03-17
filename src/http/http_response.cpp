#include "abathur/http/http_response.hpp"

#include "abathur/log.hpp"


namespace abathur::http {
    HTTPResponse::HTTPResponse(int status_code) {
        status_code_ = status_code;
    }

    HTTPResponse::~HTTPResponse() {
        LOG_TRACE << "HTTPResponse destroying, " << this;
    }

    int HTTPResponse::status_code() {
        return status_code_;
    }

    std::string HTTPResponse::content() {
        return content_;
    }
}
