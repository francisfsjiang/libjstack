#include "abathur/http/async_http_client.hpp"


#include <boost/algorithm/string.hpp>

#include "abathur/log.hpp"
#include "abathur/event.hpp"
#include "abathur/channel.hpp"
#include "abathur/io_loop.hpp"
#include "abathur/util/timer.hpp"
#include "abathur/util/buffer.hpp"
#include "abathur/http/async_http_client.hpp"
#include "abathur/http/http_response.hpp"


namespace abathur::http{
    using namespace abathur::util;

    int AsyncHTTPClient::handle_body_write(void *ptr, size_t size, size_t nmemb, HTTPResponse* resp) {
        LOG_TRACE << "Curl body write function." ;
        return resp->body_->write(static_cast<char*>(ptr), size * nmemb);
    }

    int AsyncHTTPClient::handle_header_write(char* data, size_t size, size_t nmemb, HTTPResponse* resp) {
        LOG_TRACE << "Curl header write function. "  << std::string(data, size*nmemb);
        auto header = std::string(data, size*nmemb);
        auto index = header.find(':', 0);
        if(index != std::string::npos) {
            resp->header_->insert(std::make_pair(
                    boost::algorithm::trim_copy(header.substr(0, index)),
                    boost::algorithm::trim_copy(header.substr(index + 1))
            ));
        }
        return static_cast<int>(size*nmemb);
    }

    int AsyncHTTPClient::handle_socket(CURL*, curl_socket_t curl_socket, int action, AsyncHTTPClient* userp,
                             void *socketp) {
        LOG_TRACE << "Curl socket function, action: " << action ;
        if (action == CURL_POLL_IN || action == CURL_POLL_OUT) {
            uint filter = (action == CURL_POLL_IN) ? EF_READ: EF_WRITE;

            if (socketp) {
                IOLoop::current()->update_channel_filter(curl_socket, filter);
            }
            else {
                userp->curl_socket_ = curl_socket;
                IOLoop::current()->add_channel(curl_socket, filter, userp->in_channel_);
                curl_multi_assign(userp->curl_m_handle_, curl_socket, userp);
            }
        }
        else if (action == CURL_POLL_REMOVE) {
            IOLoop::current()->remove_channel(curl_socket);
            curl_multi_assign(userp->curl_m_handle_, curl_socket, NULL);
        }
        else {
            LOG_ERROR << "Unknown curl action.";
        }
        return 0;
    }

    int AsyncHTTPClient::start_timeout(CURLM* curl_handle, long timeout_ms, AsyncHTTPClient* userp) {
        LOG_TRACE << "curl start timeout callback " << timeout_ms;
        if (timeout_ms == 0) {
            timeout_ms = 1;
        }
        if (timeout_ms < 0) {
            LOG_TRACE << "delete timer";

            //pass this
//            IOLoop::Current()->delete_timer(userp->curl_timeout_timer_);
//            userp->curl_timeout_timer_ = nullptr;
        }
//        else if (timeout_ms == 0){
//            int running_handles;
//            curl_multi_socket_action(userp->curl_handle_, CURL_SOCKET_TIMEOUT, 0, &running_handles);
//            userp->check_multi_info();
//        }
        else {
            long timeout_s = static_cast<long>(std::ceil(timeout_ms * 1.0 / 1000));

//            userp->curl_timeout_timer_ = std::make_shared<Timer>(
            auto timer = std::make_shared<Timer>(
                    static_cast<int>(util::get_time() + timeout_s),
                    util::ONCE,
                    0,
                    [=](int)->int{
                        int running_handles;
                        curl_multi_socket_action(curl_handle, CURL_SOCKET_TIMEOUT, 0, &running_handles);
                        userp->check_multi_info();
                        return 0;
                    }
            );
            userp->timers_->push_back(timer);
            IOLoop::current()->add_timer(timer);
        }
        return 0;
    }

    AsyncHTTPClient::AsyncHTTPClient() {
        LOG_TRACE << "AsyncHTTPClient constructing, " << this;
        if (curl_global_init(CURL_GLOBAL_ALL)) {
            LOG_ERROR << "Could not init cURL.";
        }
        if (!current_channel) {
            LOG_ERROR << "AsyncHTTPClient not running in a channel.";
        }
        LOG_TRACE << current_channel.use_count();
        in_channel_ = current_channel;
        LOG_TRACE << current_channel.use_count();

        done_ = false;

        curl_handle_ = curl_easy_init();
        curl_m_handle_ = curl_multi_init();

        CURLMcode ret;
        ret = curl_multi_setopt(curl_m_handle_, CURLMOPT_SOCKETFUNCTION, handle_socket);
        ret = curl_multi_setopt(curl_m_handle_, CURLMOPT_SOCKETDATA, this);
        ret = curl_multi_setopt(curl_m_handle_, CURLMOPT_TIMERFUNCTION, start_timeout);
        ret = curl_multi_setopt(curl_m_handle_, CURLMOPT_TIMERDATA, this);

        LOG_TRACE << "Curl multi setopt ret : " << ret;

        timers_ = new std::vector<std::shared_ptr<Timer>>();
    }

    AsyncHTTPClient::~AsyncHTTPClient() {
        LOG_TRACE << "AsyncHTTPClient deconstructing, " << this;
        for (auto t: *timers_) {
            t->cancel();
        }
        timers_->clear();

        if (curl_handle_) {
            curl_easy_cleanup(curl_handle_);
        }
        curl_multi_cleanup(curl_m_handle_);
        in_channel_ = nullptr;
    }

    void AsyncHTTPClient::prepare_request(const HTTPRequest& request) {
        CURLcode ret;
        ret = curl_easy_setopt(curl_handle_, CURLOPT_URL, request.host_.data());

        if (request.method_ == HTTP_METHOD::POST){
            ret = curl_easy_setopt(curl_handle_, CURLOPT_POSTFIELDS, request.post_buffer_->data_to_read());
            ret = curl_easy_setopt(curl_handle_, CURLOPT_POSTFIELDSIZE, request.post_buffer_->size());
        }

        #if defined(ABATHUR_TRACE)
        curl_easy_setopt(curl_handle_, CURLOPT_VERBOSE, 1L);
        #endif

//        ret = curl_easy_setopt(curl_handle_, CURLOPT_PROXY, "http://my.proxy.net");   // replace with your actual proxy
//        ret = curl_easy_setopt(curl_handle_, CURLOPT_PROXYPORT, 8080L);

        struct curl_slist *header_list = NULL;
        for(const auto& header: *(request.header_)) {
            header_list = curl_slist_append(header_list, (header.first + ": " + header.second).data());
        }
        ret = curl_easy_setopt(curl_handle_, CURLOPT_HTTPHEADER, header_list);

//        ret = curl_easy_setopt(curl_handle_, CURLOPT_HEADER, 1L);
        ret = curl_easy_setopt(curl_handle_, CURLOPT_WRITEFUNCTION, handle_body_write);
        ret = curl_easy_setopt(curl_handle_, CURLOPT_WRITEDATA, response_);
        ret = curl_easy_setopt(curl_handle_, CURLOPT_HEADERFUNCTION, handle_header_write);
        ret = curl_easy_setopt(curl_handle_, CURLOPT_HEADERDATA, response_);

        LOG_TRACE << "Curl easy setopt ret : " << ret;
        curl_multi_add_handle(curl_m_handle_, curl_handle_);

    }

    HTTPResponse* AsyncHTTPClient::perform_request(const HTTPRequest& request) {
        response_ = new HTTPResponse();
        prepare_request(request);
        // wait for IOLoop
        LOG_TRACE << "AsyncHTTPClient loop.";

        this->process_loop();

        return new HTTPResponse(*response_);
    }

    int AsyncHTTPClient::process_event(const Event &event) {
        int flags = 0;
        int running_handles;
        if (event.closeable())
            flags = CURL_CSELECT_ERR;
        if (!event.closeable() && event.readable()) flags |= CURL_CSELECT_IN;
        if (!event.closeable() && event.writable()) flags |= CURL_CSELECT_OUT;
        curl_multi_socket_action(curl_m_handle_, event.get_fd(), flags, &running_handles);
        int ret = check_multi_info();
        if (ret == 0) {
            IOLoop::current()->remove_channel(curl_socket_);
            return 0;
        }
        return 1;
    }



    void AsyncHTTPClient::prepare_response() {
        long version, status_code;
        curl_easy_getinfo(curl_handle_, CURLINFO_HTTP_VERSION, &version);
        curl_easy_getinfo(curl_handle_, CURLINFO_RESPONSE_CODE, &status_code);
        response_->status_code_ = static_cast<int>(status_code);
        switch (version){
            case CURL_HTTP_VERSION_1_0:
                response_->version_ = HTTP_VERSION::HTTP1_0;
                break;
            case CURL_HTTP_VERSION_1_1:
                response_->version_ = HTTP_VERSION::HTTP1_1;
                break;
            case CURL_HTTP_VERSION_2_0:
                response_->version_ = HTTP_VERSION::HTTP2_0;
                break;
            default:
                response_->version_ = HTTP_VERSION::HTTPNone;
        }
    }

    int AsyncHTTPClient::check_multi_info() {
        LOG_TRACE << "Check curl multi info.";
        char *done_url;
        CURLMsg *message;
        int pending;

        while ((message = curl_multi_info_read(curl_m_handle_, &pending))) {
            switch (message->msg) {
                case CURLMSG_DONE:
                    curl_easy_getinfo(message->easy_handle, CURLINFO_EFFECTIVE_URL,
                                      &done_url);
                    LOG_DEBUG << done_url << "DONE";
                    done_ = true;

                    prepare_response();

                    curl_multi_remove_handle(curl_m_handle_, message->easy_handle);
                    curl_easy_cleanup(message->easy_handle);
                    curl_handle_ = nullptr;
                    break;

                default:
                    LOG_DEBUG << "CURLMSG default";
            }
        }
        if (done_)
            return 0;
        else
            return 2;
    }
}
