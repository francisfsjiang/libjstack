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

        std::shared_ptr<EventProcessor> p = shared_from_this();
        std::shared_ptr<Channel> channel(
                new Channel(p)
        );
        abathur::IOLoop::Current()->AddChannel(socket_ptr_->GetFD(), channel);

    }

    void SocketHandler::ProcessEvent(const Event & event) {
        if (event.Readable()) {
            socket_ptr_->Recv(read_buffer_.data(), read_buffer_.capacity());
        }
    }

    int SocketHandler::Write(const char * data, size_t size) {
        return write_buffer_.write(data, size);
    }

}
