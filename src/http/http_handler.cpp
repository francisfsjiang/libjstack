#include "abathur/http/http_handler.hpp"


#include "abathur/log.hpp"
#include "abathur/http/http_parser.hpp"
#include "abathur/http/http_response.hpp"

namespace abathur::http {
    using namespace abathur::net;

    HTTPHandler::HTTPHandler(Socket* socket): abathur::net::SocketHandler(socket){
        LOG_TRACE << "HTTPHandler constructing, " << this;
        parser_ = new HTTPParser(HTTP_TYPE::REQUEST);
    }

    HTTPHandler::~HTTPHandler() {
        LOG_TRACE << "HTTPHandler deconstructing, " << this;
    }

    int HTTPHandler::handle_socket_data(util::Buffer& buffer) {

        int ret = parser_->perform_parsing(buffer);
        if (parser_->complete()) {

            request_ = parser_->get_request();

            response_ = handle_http_request(*request_);
            response_->write_to_buffer(write_buffer_);
        }

        return ret;
    }

}