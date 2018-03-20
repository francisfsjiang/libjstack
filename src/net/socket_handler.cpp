#include "abathur/net/socket_handler.hpp"

#include <sys/socket.h>

#include "abathur/util/buffer.hpp"
#include "abathur/net/socket.hpp"
#include "abathur/io_loop.hpp"
#include "abathur/channel.hpp"
#include "abathur/log.hpp"
#include "abathur/event.hpp"

namespace abathur::net {


    SocketHandler::SocketHandler(Socket* socket) {
        LOG_TRACE << "SocketHandler constructing, " << this;
        socket_ptr_ = socket;
    }

    SocketHandler::~SocketHandler() {
        LOG_TRACE << "SocketHandler deconstructing, " << this;
        delete socket_ptr_;
    }

    int SocketHandler::Init() {

        socket_ptr_->set_non_blocking(true);
        socket_ptr_->set_tcp_no_delay(true);

//        auto p = shared_from_this();
//        auto self = std::dynamic_cast<SocketHandler>(p);
        auto channel_ptr = std::shared_ptr<Channel>(new Channel(dynamic_cast<EventProcessor*>(this)));

        LOG_TRACE << channel_ptr.use_count();
        abathur::IOLoop::current()->add_channel(socket_ptr_->get_fd(), EF_READ | EF_CLOSE, channel_ptr);
        LOG_TRACE << channel_ptr.use_count();

        return 0;
    }

    int SocketHandler::process_event(const Event &event) {
        if (event.closeable()) {
            IOLoop::current()->remove_channel(socket_ptr_->get_fd());
            return 0;
        }


        if (event.readable()) {
            socket_ptr_->recv(read_buffer_);

            int ret = handle_socket_data(read_buffer_);
            if (ret > 0) {
                read_buffer_.set_reader_pos(read_buffer_.get_reader_pos()+ret);
                read_buffer_.shrink();
            }
        }

        if (write_buffer_.size() > 0) {
            socket_ptr_->send(write_buffer_);
            if (write_buffer_.size() != 0) {
                if(!wait_for_write_event_){
                    IOLoop::current()->update_channel_filter(socket_ptr_->get_fd(), EF_WRITE);
                    wait_for_write_event_ = true;
                }
            }
            else if(wait_for_write_event_){
                IOLoop::current()->set_channel_filter(socket_ptr_->get_fd(), EF_READ | EF_CLOSE);
                wait_for_write_event_ = false;
            }
        }

        //TODO: Handle close events.

        if (write_buffer_.size() == 0 && finished_) {
            IOLoop::current()->remove_channel(socket_ptr_->get_fd());
            return 0;
        }
        return 1;
    }

    int SocketHandler::write(const char *data, size_t size) {
        return write_buffer_.write(data, size);
    }

    void SocketHandler::finish() {
        finished_ = true;
    }

}
