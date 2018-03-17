#include "abathur/http/async_http_client.hpp"

#include "abathur/log.hpp"
#include "abathur/event.hpp"
#include "abathur/channel.hpp"
#include "abathur/io_loop.hpp"
#include "abathur/http/http_request.hpp"
#include "abathur/http/http_response.hpp"
#include "abathur/util/buffer.hpp"


namespace abathur::http{

    AsyncHTTPClient::AsyncHTTPClient() {
        if (curl_global_init(CURL_GLOBAL_ALL)) {
            LOG_ERROR << "Could not init cURL.";
        }

        recv_buffer_ = new util::Buffer;

        curl_handle_ = curl_multi_init();

        curl_multi_setopt(curl_handle_, CURLMOPT_SOCKETFUNCTION, [=](
                CURL*, curl_socket_t curl_socket, int action, void*, void *socketp
        ){
            if (action == CURL_POLL_IN || action == CURL_POLL_OUT) {
                if (socketp) {
                    IOLoop::Current()->UpdateChannel(curl_socket, EF_READ);
                }
                else {
                    curl_socket_ = curl_socket;
                    IOLoop::Current()->AddChannel(curl_socket, EF_READ, current_channel);
                    curl_multi_assign(curl_handle_, curl_socket, current_channel);
                }
            }
            else if (action == CURL_POLL_REMOVE) {
                IOLoop::Current()->RemoveChannel(curl_socket);
                curl_multi_assign(curl_handle_, curl_socket, NULL);
            }
            else {
                LOG_ERROR << "Unknown curl action.";
            }
            return 0;
        });

        curl_multi_setopt(curl_handle_, CURLMOPT_TIMERFUNCTION, [=]
                (CURLM*, long, void*){
            //TODO make timer

        });
    }

    AsyncHTTPClient::~AsyncHTTPClient() {
        curl_multi_cleanup(curl_handle_);
    }

    void AsyncHTTPClient::prepare_request(const HTTPRequest& request) {

        CURL *handle = curl_easy_init();
        curl_easy_setopt(handle, CURLOPT_URL, request.host_.data());

        if (request.method_ == POST){
            curl_easy_setopt(handle, CURLOPT_POSTFIELDS, request.post_buffer_->data_to_read());
            curl_easy_setopt(handle, CURLOPT_POSTFIELDSIZE, request.post_buffer_->size());
        }

        curl_easy_setopt(handle, CURLOPT_VERBOSE, 1L);
//        curl_easy_setopt(handle, CURLOPT_PROXY, "http://my.proxy.net");   // replace with your actual proxy
//        curl_easy_setopt(handle, CURLOPT_PROXYPORT, 8080L);

        struct curl_slist *header_list = NULL;
        for(const auto& header: request.header_) {
            header_list = curl_slist_append(header_list, (header.first + ": " + header.second).data());
        }
        curl_easy_setopt(handle, CURLOPT_HTTPHEADER, header_list);


        curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION,
                         [](void* ptr, size_t size, size_t nmemb, util::Buffer* buffer){
                             return buffer->write(static_cast<char*>(ptr), size * nmemb);
                         });
        curl_easy_setopt(handle, CURLOPT_WRITEDATA, &recv_buffer_);

        curl_multi_add_handle(curl_handle_, handle);

    }

    HTTPResponse AsyncHTTPClient::perform_request(const HTTPRequest& request) {
        prepare_request(request);
        // wait for IOLoop
        auto routine_in = current_channel->get_routine_in();
        while (true) {
            auto event = routine_in->get();
            int flags = 0;
            int running_handles;
            if (event.Closeable())
                flags = CURL_CSELECT_ERR;
            if (!event.Closeable() && event.Readable()) flags |= CURL_CSELECT_IN;
            if (!event.Closeable() && event.Writable()) flags |= CURL_CSELECT_OUT;
            curl_multi_socket_action(curl_handle_, event.GetFD(), flags, &running_handles);
            int ret = check_multi_info();
            if (ret == 0) {
                IOLoop::Current()->RemoveChannel(curl_socket_);
                break;
            }
        }
        return prepare_response();

    }

    HTTPResponse AsyncHTTPClient::prepare_response() {
        return HTTPResponse(200);
    }

    int AsyncHTTPClient::check_multi_info() {
        char *done_url;
        CURLMsg *message;
        int pending;

        bool done = false;

        while ((message = curl_multi_info_read(curl_handle_, &pending))) {
            switch (message->msg) {
                case CURLMSG_DONE:
                    curl_easy_getinfo(message->easy_handle, CURLINFO_EFFECTIVE_URL,
                                      &done_url);
                    LOG_DEBUG << done_url << "DONE";
                    done = true;
                    curl_multi_remove_handle(curl_handle_, message->easy_handle);
                    curl_easy_cleanup(message->easy_handle);
                    break;

                default:
                    LOG_DEBUG << "CURLMSG default";
            }
        }
        if (done)
            return 0;
        else
            return 2;
    }
}
