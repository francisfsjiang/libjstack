#include "abathur/http/http_handler.hpp"

#include "abathur/http/http_request.hpp"
#include "abathur/http/http_response.hpp"

namespace abathur::http {
    HTTPHandler::HTTPHandler() {
        finished_ = false;
    }

    HTTPHandler::~HTTPHandler() {

    }

    void HTTPHandler::finish() {
        finished_ = true;
    }



    HTTPResponse* HTTPHandler::handle_get(const HTTPRequest& req) {
        auto resp = new abathur::http::HTTPResponse();
        resp->set_status_code(HTTPStatus::NOT_FOUND);
        finish();
        return resp;
    }

    HTTPResponse* HTTPHandler::handle_post(const HTTPRequest& req) {
        auto resp = new abathur::http::HTTPResponse();
        resp->set_status_code(HTTPStatus::NOT_FOUND);
        finish();
        return resp;
    }

    HTTPResponse* HTTPHandler::handle_put(const HTTPRequest& req) {
        auto resp = new abathur::http::HTTPResponse();
        resp->set_status_code(HTTPStatus::NOT_FOUND);
        finish();
        return resp;
    }

    HTTPResponse* HTTPHandler::handle_delete(const HTTPRequest& req) {
        auto resp = new abathur::http::HTTPResponse();
        resp->set_status_code(HTTPStatus::NOT_FOUND);
        finish();
        return resp;
    }
}
