#include "abathur/http/http_request.hpp"

#include "abathur/util/buffer.hpp"
#include "abathur/log.hpp"

namespace abathur::http {
    HTTPRequest::HTTPRequest(const std::string& host) {
        prepare(host, GET);
    }

    HTTPRequest::HTTPRequest(const std::string& host, HTTP_METHOD method) {
        prepare(host, method);
    }

    void HTTPRequest::prepare(const std::string& host, HTTP_METHOD method) {
        host_ = host;
        method_ = method;

        header_["User-Agent"] = "Abathur/0.1";
        version_ = HTTP1_1;
    }

    HTTPRequest::~HTTPRequest() {
        LOG_TRACE << "HTTPRequest destroying, " << this;
    }

    int HTTPRequest::set_post_data(const char* data, size_t size) {
        return post_buffer_->write(data, size);
    }

    void HTTPRequest::set_header(const std::string& key, const std::string& value) {
        header_[key] = value;
    }

    void HTTPRequest::set_version(HTTP_VERSION version) {
        version_ = version;
    }

}
