#include "abathur/net/socket_server.hpp"

#include <cstring>

#include "abathur/io_loop.hpp"
#include "abathur/channel.hpp"
#include "abathur/event.hpp"
#include "abathur/net/socket_handler.hpp"

#include "abathur/net/inet_address.hpp"
#include "abathur/net/socket.hpp"


namespace abathur::net {


    SocketServer::SocketServer(std::shared_ptr<InetAddress> address) {


        std::shared_ptr<Channel> channel_ptr(new Channel(shared_from_this()));

        socket_ = std::shared_ptr<Socket>(new Socket(address));

        LOG_DEBUG << "fd" << socket_->GetFD() << " Listen established";

        abathur::IOLoop::Current()->AddChannel(socket_->GetFD(), channel_ptr);
    }

    void SocketServer::ProcessEvent(const Event& event) {

        LOG_DEBUG << "fd" << event.GetFD()<< " have connections";


        while (true) {
            auto new_socket = socket_->Accept();
            if (!new_socket) break;

            std::shared_ptr<SocketHandler> socket_handler(socket_handler_generator_(new_socket));
            std::shared_ptr<Channel> channel(new Channel(socket_handler));
        }

    }

}
