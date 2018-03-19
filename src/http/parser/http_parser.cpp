#include "abathur/http/parser/http_parser.hpp"

#include <string>

#include "abathur/log.hpp"
#include "abathur/util/buffer.hpp"

namespace abathur::http::parser {

    using namespace abathur::util;

    HTTPParser::HTTPParser(Buffer* buffer, http_parser_type type) {
        LOG_DEBUG << "http-parser version: " << http_parser_version();
        buffer_ = buffer;
        parser_ = new http_parser();
        http_parser_init(parser_, type);
        parser_->data = this;
    }

    HTTPParser::~HTTPParser() {
        delete parser_;
    }

    int HTTPParser::perform_parsing() {
        LOG_TRACE << buffer_->data_to_read();
        size_t ret = http_parser_execute(parser_, &parser_settings_, buffer_->data_to_read(), buffer_->size());
        LOG_DEBUG << http_errno_name(http_errno(parser_->http_errno));
        LOG_DEBUG << http_errno_description(http_errno(parser_->http_errno));
        return 0;
    }

    int HTTPParser::on_message_begin(http_parser* parser) {
        LOG_TRACE << "on_message_begin";
        return 0;
    }

    int HTTPParser::on_url(http_parser* parser, const char* data, size_t size) {
        LOG_TRACE << "on_url";
        return 0;

    }

    int HTTPParser::on_status(http_parser* parser, const char* data, size_t size) {
        LOG_TRACE << "on_status";
        return 0;

    }

    int HTTPParser::on_header_field(http_parser* parser, const char* data, size_t size) {
        LOG_TRACE << "on_header_field";
        return 0;

    }

    int HTTPParser::on_header_value(http_parser* parser, const char* data, size_t size) {
        LOG_TRACE << "on_header_value";
        return 0;

    }

    int HTTPParser::on_header_complete(http_parser* parser) {
        LOG_TRACE << "on_header_complete";
        return 0;

    }

    int HTTPParser::on_body(http_parser* parser, const char* data, size_t size) {
        LOG_TRACE << "on_body";
        return 0;

    }

    int HTTPParser::on_message_complete(http_parser* parser) {
        LOG_TRACE << "on_message_complete";
        return 0;

    }

    int HTTPParser::on_chunk_header(http_parser* parser) {
        LOG_TRACE << "on_chunk_header";
        return 0;

    }

    int HTTPParser::on_chunk_complete(http_parser* parser) {
        LOG_TRACE << "on_chunk_complete";
        return 0;
    }

}