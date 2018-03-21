#include "abathur/http/http_request.hpp"

#include "abathur/http/http_parser.hpp"
#include "abathur/util/buffer.hpp"
#include "abathur/log.hpp"

namespace abathur::http {

    using namespace util;

    HTTPRequest::HTTPRequest() {
        LOG_TRACE << "HTTPRequest constructing, " << this;
        body_ = new Buffer();
        header_ = new std::map<std::string, std::string>();
    }

    HTTPRequest::HTTPRequest(const std::string& host) {
        LOG_TRACE << "HTTPRequest constructing, " << this;
        prepare(host, HTTP_METHOD::GET);
    }

    HTTPRequest::HTTPRequest(const std::string& host, HTTP_METHOD method) {
        LOG_TRACE << "HTTPRequest constructing, " << this;
        prepare(host, method);
    }

    HTTPRequest::HTTPRequest(const HTTPRequest& req) {
        LOG_TRACE << "HTTPRequest constructing, " << this;
        method_ = req.method_;
        host_ = req.host_;
        header_ = new std::map<std::string, std::string>(*req.header_);
        body_ = new Buffer(*req.body_);
    }

    void HTTPRequest::prepare(const std::string& host, HTTP_METHOD method) {
        host_ = host;
        method_ = method;
        header_ = new std::map<std::string, std::string>();
        if (method_ == HTTP_METHOD::POST) {
            body_ = new Buffer();
        }

        header_->insert(std::make_pair("User-Agent","Abathur/0.1"));
        version_ = HTTPVersion::HTTP1_1;
    }

    HTTPRequest::~HTTPRequest() {
        LOG_TRACE << "HTTPRequest deconstructing, " << this;
    }

    int HTTPRequest::write_post_data(const char* data, size_t size) {
        return body_->write(data, size);
    }

    const util::Buffer* HTTPRequest::get_body() const {
        return body_;
    }

    void HTTPRequest::set_header(const std::string& key, const std::string& value) {
        header_->insert(std::make_pair(key, value));
    }

    void HTTPRequest::set_version(HTTPVersion version) {
        version_ = version;
    }

    HTTP_METHOD HTTPRequest::get_method() const {
        return method_;
    }

    std::string HTTPRequest::get_url() const {
        return url_;
    }

}
