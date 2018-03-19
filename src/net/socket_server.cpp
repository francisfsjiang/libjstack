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

        LOG_TRACE << "Listen established on fd " << socket_->GetFD() ;
    }

    int SocketServer::Init(){
        if (!inited_){
//            auto self = std::dynamic_pointer_cast<SocketServer>(shared_from_this());
//            auto self = shared_from_this();
            //GetSelf();
            std::shared_ptr<Channel> channel_ptr(new Channel(dynamic_cast<EventProcessor*>(this)));

            socket_->Bind();
            socket_->Listen();
            socket_->SetNonBlocking(true);
            socket_->SetReusePort(true);
            socket_->SetReuseAddr(true);

            abathur::IOLoop::Current()->AddChannel(socket_->GetFD(), EF_READ, channel_ptr);

            inited_ = true;
        }
        return 0;
    }

    void SocketServer::ProcessEvent(const Event& event) {
        Init();

        LOG_TRACE << "SocketServer fd " << event.GetFD()<< " have incomming connections";


        while (true) {
            auto new_socket = socket_->Accept();
            if (!new_socket) break;

            new_socket->SetNonBlocking(true);
            SocketHandler* s = socket_handler_generator_(new_socket);
            s->Init();
        }

    }

    SocketServer::~SocketServer() {
        LOG_TRACE << "SocketServer deconstructing, " << this;
        delete socket_;
    }
}
