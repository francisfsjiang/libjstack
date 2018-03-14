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

    int SocketHandler::Init() {

        auto p = shared_from_this();
        auto self = std::dynamic_pointer_cast<SocketHandler>(p);
        std::shared_ptr<Channel> channel_ptr(new Channel(self));

        abathur::IOLoop::Current()->AddChannel(socket_ptr_->GetFD(), channel_ptr);

        return 0;
    }

    void SocketHandler::ProcessEvent(const Event & event) {
        if (event.Readable()) {
            socket_ptr_->Recv(read_buffer_.data(), read_buffer_.capacity());
        }
    }

    int SocketHandler::Write(const char * data, size_t size) {
        return write_buffer_.write(data, size);
    }

    void SocketHandler::Process(const char* , size_t ) {

    }

}
