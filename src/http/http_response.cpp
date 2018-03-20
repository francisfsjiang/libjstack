#include <abathur/abathur.hpp>

#include <sstream>

#include "abathur/http/http_response.hpp"
#include "abathur/http/http_parser.hpp"

#include "abathur/log.hpp"


namespace abathur::http {
    using namespace abathur::util;
    using namespace std;

    const map<HTTP_VERSION, string> HTTP_VERSION_TO_STRING{
            {HTTP_VERSION::HTTP1_0, "HTTP/1.0"},
            {HTTP_VERSION::HTTP1_1, "HTTP/1.1"},
    };

    HTTPResponse::HTTPResponse() {
        LOG_TRACE << "HTTPResponse constructing, " << this;
        status_code_ = 200;
        body_ = new Buffer();
        header_ = new map<string, string>{
                {"Content-Type", "text/html; charset=utf-8"},
                {"Server", "Abathur/0.1"},
        };
        version_ = HTTP_VERSION::HTTP1_1;
    }

    HTTPResponse::HTTPResponse(const HTTPResponse& resp) {
        LOG_TRACE << "HTTPResponse constructing, " << this;
        version_ = resp.version_;
        status_code_ = resp.status_code_;
        body_ = new Buffer(*resp.body_);
        header_ = new map<string, string>(*resp.header_);
    }

    HTTPResponse::~HTTPResponse() {
        LOG_TRACE << "HTTPResponse deconstructing, " << this;
        delete body_;
        delete header_;
    }

    int HTTPResponse::status_code() {
        return status_code_;
    }

    Buffer* HTTPResponse::get_body() {
        return new Buffer(*body_);
    }

    map<string, string>* HTTPResponse::get_header() {
        return new map<string, string>(*header_);
    }

    void HTTPResponse::set_header(const std::string& field, const std::string& value) {
        header_->insert(make_pair(field, value));
    }

    size_t HTTPResponse::write(const std::string& s) {
        return body_->write(s.data(), s.size());
    }

    size_t HTTPResponse::write(const char* data, size_t size) {
        return body_->write(data, size);
    }

    size_t HTTPResponse::write_to_buffer(util::Buffer &buffer) {
        size_t old_size = buffer.size();
        ostringstream sstream;
        sstream << HTTP_VERSION_TO_STRING.find(version_)->second;
        sstream << " ";
        sstream << status_code_;
        sstream << " ";
        sstream << HTTP_STATUS_TO_DESCRIPTION.find(status_code_)->second;
        sstream << "\r\n";

        ostringstream c;
        c << body_->size();
        LOG_TRACE << c.str();
        header_->insert(make_pair("Content-Length", c.str()));
        for (auto i: *header_) {
            sstream << i.first << ": " << i.second << "\r\n";
        }
        sstream << "\r\n";
        auto s = sstream.str();
        buffer.write(s.data(), s.size());
//        buffer.write()
        buffer.write(body_->data_to_read(), body_->size());
        return buffer.size() - old_size;
    }
}
