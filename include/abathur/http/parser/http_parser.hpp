#ifndef _ABATHUR_HTTP_PARSER_HTTP_PARSER_HPP_
#define _ABATHUR_HTTP_PARSER_HTTP_PARSER_HPP_

#include "http_parser.h"

namespace abathur::util {
    class Buffer;
}

namespace abathur::http {
    class HTTPResponse;
    class HTTPRequest;
}

namespace abathur::http::parser {

    typedef int (*http_data_cb) (http_parser*, const char *at, size_t length);
    typedef int (*http_cb) (http_parser*);

    class HTTPParser{
        friend class abathur::http::HTTPResponse;
        friend class abathur::http::HTTPRequest;
    private:
        static int on_message_begin(http_parser*);
        static int on_url(http_parser*, const char*, size_t);
        static int on_status(http_parser*, const char*, size_t);
        static int on_header_field(http_parser*, const char*, size_t);
        static int on_header_value(http_parser*, const char*, size_t);
        static int on_header_complete(http_parser*);
        static int on_body(http_parser*, const char*, size_t);
        static int on_message_complete(http_parser*);
        static int on_chunk_header(http_parser*);
        static int on_chunk_complete(http_parser*);

        constexpr static const http_parser_settings parser_settings_ = {
                on_message_begin,
                on_url,
                on_status,
                on_header_field,
                on_header_value,
                on_header_complete,
                on_body,
                on_message_complete,
                on_chunk_header,
                on_chunk_complete
        };

        http_parser* parser_;
        util::Buffer* buffer_;

        util::Buffer* body_;

    public:
        HTTPParser(util::Buffer*, http_parser_type);
        ~HTTPParser();

        int perform_parsing();

    };
}


#endif //_ABATHUR_HTTP_PARSER_HTTP_PARSER_HPP_
