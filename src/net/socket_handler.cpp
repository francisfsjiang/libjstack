#include "abathur/net/socket_handler.hpp"

#include <sys/socket.h>

#include "abathur/util/buffer.hpp"
#include "abathur/net/socket.hpp"
#include "abathur/io_loop.hpp"
#include "abathur/channel.hpp"
#include "abathur/log.hpp"
#include "abathur/event.hpp"

namespace abathur::net {


    SocketHandler::SocketHandler(std::shared_ptr<Socket> socket) {
        socket_ptr_ = socket;
    }

    SocketHandler::~SocketHandler() {
        LOG_TRACE << "SocketHandler deleted, address " << this;
    }

    int SocketHandler::Init() {

        auto p = shared_from_this();
        auto self = std::dynamic_pointer_cast<SocketHandler>(p);
        std::shared_ptr<Channel> channel_ptr(new Channel(self));

        abathur::IOLoop::Current()->AddChannel(socket_ptr_->GetFD(), EF_READ, channel_ptr);

        return 0;
    }

    void SocketHandler::ProcessEvent(const Event & event) {
        if (event.Readable()) {
            socket_ptr_->Recv(read_buffer_);
        }

        Process(read_buffer_);

        if (write_buffer_.size() > 0) {
            if(event.Writable()){
                socket_ptr_->Send(write_buffer_);
            }
            else {
                IOLoop::Current()->UpdateChannel(socket_ptr_->GetFD(), EF_READ | EF_WRITE);
            }
        }


    }

    int SocketHandler::Write(const char * data, size_t size) {
        return write_buffer_.write(data, size);
    }

}
