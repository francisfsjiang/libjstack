#include <abathur/abathur.hpp>


#include "abathur/http/http_response.hpp"
#include "abathur/http/parser/http_parser.hpp"

#include "abathur/log.hpp"


namespace abathur::http {
    HTTPResponse::HTTPResponse() {
        body_ = new Buffer();
        header_ = new std::map<std::string, std::string>;
    }

    HTTPResponse::HTTPResponse(const HTTPResponse& resp) {
        version_ = resp.version_;
        status_code_ = resp.status_code_;
        body_ = new Buffer(*resp.body_);
        header_ = new std::map<std::string, std::string>(*resp.header_);
    }

    HTTPResponse::~HTTPResponse() {
        LOG_TRACE << "HTTPResponse destroying, " << this;
    }

    int HTTPResponse::status_code() {
        return status_code_;
    }

    Buffer* HTTPResponse::get_body() {
        return new Buffer(*body_);
    }

    std::map<std::string, std::string>* HTTPResponse::get_header() {
        return new std::map<std::string, std::string>(*header_);
    }
}
