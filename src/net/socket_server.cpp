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


    SocketServer::SocketServer(std::shared_ptr<InetAddress> address) {
        socket_ = std::shared_ptr<Socket>(new Socket(address));

        LOG_DEBUG << "fd" << socket_->GetFD() << " Listen established";
    }

    int SocketServer::Init(){
        if (!inited_){
            auto self = std::dynamic_pointer_cast<SocketServer>(shared_from_this());
            //GetSelf();
            std::shared_ptr<Channel> channel_ptr(new Channel(self));

            socket_->Bind();
            socket_->Listen();
            socket_->SetNonBlocking(true);
            socket_->SetReusePort(true);
            socket_->SetReuseAddr(true);

            abathur::IOLoop::Current()->AddChannel(socket_->GetFD(), channel_ptr);

            inited_ = true;
        }
        return 0;
    }

    void SocketServer::ProcessEvent(const Event& event) {
        Init();

        LOG_DEBUG << "fd" << event.GetFD()<< " have connections";


        while (true) {
            auto new_socket = socket_->Accept();
            if (!new_socket) break;

            new_socket->SetNonBlocking(true);
            SocketHandler* s = socket_handler_generator_(new_socket);
            std::shared_ptr<SocketHandler> sp(s);
            sp->Init();
        }

    }

}
