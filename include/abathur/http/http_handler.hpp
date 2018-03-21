#ifndef _ABATHUR_HTTP_HTTP_HANDLER_HPP_
#define _ABATHUR_HTTP_HTTP_HANDLER_HPP_

namespace abathur::http {
    class HTTPResponse;
    class HTTPRequest;

    class HTTPHandler{
    private:
        bool finished_;
    public:
        HTTPHandler();
        virtual ~HTTPHandler();

        void finish();

        virtual HTTPResponse* handle_get(const HTTPRequest&);
        virtual HTTPResponse* handle_post(const HTTPRequest&);
        virtual HTTPResponse* handle_put(const HTTPRequest&);
        virtual HTTPResponse* handle_delete(const HTTPRequest&);
    };
}

#endif //_ABATHUR_HTTP_HANDLER_HPP_
