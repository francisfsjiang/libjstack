#include "abathur/http/http_handler_wrapper.hpp"

#include <map>
#include <functional>

#include "abathur/log.hpp"
#include "abathur/http/http_parser.hpp"
#include "abathur/http/http_response.hpp"
#include "abathur/http/http_handler.hpp"

namespace abathur::http {
    using namespace abathur::net;
    using namespace std;

    HTTPHandlerWrapper::HTTPHandlerWrapper(Socket* socket): abathur::net::SocketHandler(socket){
        LOG_TRACE << "HTTPHandlerWrapper constructing, " << this;
        parser_ = new HTTPParser(HTTP_TYPE::REQUEST);
    }

    HTTPHandlerWrapper::~HTTPHandlerWrapper() {
        LOG_TRACE << "HTTPHandlerWrapper deconstructing, " << this;
    }

    int HTTPHandlerWrapper::init(void* p) {
        if (p) {
            router_ = static_cast<RouterType*>(p);
        }
        else {
            LOG_FATAL << "No router found.";
        }

        SocketHandler::init(nullptr);
        return 0;
    }

    const map<HTTP_METHOD, function<HTTPResponse*(HTTPHandler*, const HTTPRequest&)>> HTTP_METHOD_TO_HANDLER_FUNC {
            {HTTP_METHOD::GET,    &HTTPHandler::handle_get},
            {HTTP_METHOD::POST,   &HTTPHandler::handle_post},
            {HTTP_METHOD::PUT,    &HTTPHandler::handle_put},
            {HTTP_METHOD::DELETE, &HTTPHandler::handle_delete},
    };

    size_t HTTPHandlerWrapper::handle_socket_data(util::Buffer& buffer) {
        size_t ret = parser_->perform_parsing(buffer);
//        buffer.set_reader_pos(buffer.get_reader_pos() + ret);
//        buffer.shrink();

        HTTPRequest* request = parser_->get_request();
        while (request) {
            auto response = dispatch_request(*request);
            response->write_to_buffer(write_buffer_);
            if (!response) {
                response = new HTTPResponse();
                response->set_status_code(HTTPStatus::BAD_REQUEST);
            }
            delete request;
            request = nullptr;
            delete response;

            request = parser_->get_request();
        }

        return ret;
    }

    HTTPResponse* HTTPHandlerWrapper::dispatch_request(const HTTPRequest& request) {

        HTTPHandler* handler = nullptr;
        HTTPResponse* response = nullptr;
        std::string url = request.get_url();
        for (auto router_record: *router_) {
            if(regex_match(url, router_record.first)) {
                handler = router_record.second();
                break;
            }
        }
        if (!handler) {
            return nullptr;
        }

        auto handle_func_iter = HTTP_METHOD_TO_HANDLER_FUNC.find(request.get_method());
        if (handle_func_iter != HTTP_METHOD_TO_HANDLER_FUNC.end()) {
            response = (handle_func_iter->second)(handler, request);
            return response;
        }
        return nullptr;
    }

}