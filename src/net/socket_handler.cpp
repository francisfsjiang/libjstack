#include "abathur/net/socket_handler.hpp"

#include <sys/socket.h>

#include "abathur/net/socket.hpp"
#include "abathur/io_loop.hpp"
#include "abathur/channel.hpp"
#include "abathur/log.hpp"

namespace abathur::net {


    SocketHandler::SocketHandler(std::shared_ptr<Socket> socket) {
        socket_ptr_ = socket;

        std::shared_ptr<EventProcessor> p = shared_from_this();
        std::shared_ptr<Channel> channel(
                new Channel(p)
        );
        abathur::IOLoop::Current()->AddChannel(socket_ptr_->GetFD(), channel);

    }

    void SocketHandler::WriteMsg(const std::string &msg) {
        //CallbackHandler e(fd_, this);
        //e.set_write_callback<SocketHandler>(&SocketHandler::WriteCallback);
        //IOLoop::Current()->AddEventCallback(e);
        socket_ptr_ -> Send(msg.data(), msg.size());

    }

}