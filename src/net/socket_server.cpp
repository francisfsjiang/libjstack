#include "abathur/net/socket_server.hpp"

#include <cstring>
#include <memory>

#include "abathur/io_loop.hpp"
#include "abathur/channel.hpp"
#include "abathur/event.hpp"
#include "abathur/net/socket_handler.hpp"

#include "abathur/net/inet_address.hpp"
#include "abathur/net/socket.hpp"


namespace abathur::net {


    SocketServer::SocketServer(InetAddress* address) {
        LOG_TRACE << "SocketServer constructing, " << this;
        socket_ = new Socket(address);

        LOG_TRACE << "Listen established on fd " << socket_->get_fd() ;
    }

    int SocketServer::init(){
        if (inited_){
            return 0;
        }
//            auto self = std::dynamic_pointer_cast<SocketServer>(shared_from_this());
//            auto self = shared_from_this();
        //GetSelf();
        std::shared_ptr<Channel> channel_ptr(new Channel(dynamic_cast<EventProcessor*>(this)));

        socket_->bind();
        socket_->listen();
        socket_->set_non_blocking(true);
        socket_->set_reuse_port(true);
        socket_->set_reuse_addr(true);

        abathur::IOLoop::current()->add_channel(socket_->get_fd(), EF_READ, channel_ptr);

        inited_ = true;
        return 0;
    }

    int SocketServer::process_event(const Event &event) {
        init();

        LOG_TRACE << "SocketServer fd " << event.get_fd()<< " have incomming connections";


        while (true) {
            auto new_socket = socket_->accept();
            if (!new_socket) break;

            new_socket->set_non_blocking(true);
            SocketHandler* s = socket_handler_generator_(new_socket);
            s->init(nullptr);
        }
        return 1;
    }

    SocketServer::~SocketServer() {
        LOG_TRACE << "SocketServer deconstructing, " << this;
        delete socket_;
    }
}
