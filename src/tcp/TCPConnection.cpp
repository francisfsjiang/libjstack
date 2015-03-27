//
// Created by Neveralso on 15/3/19.
//

#include "TCPConnection.h"

namespace dc {

TCPConnection::TCPConnection(const int &fd,
                             const std::string &from_address,
                             const std::function<void *()> &handler_generator,
                             TCPServer *tcp_server) {
    fd_ = fd;
    from_address_ = from_address;
    tcp_server_ = tcp_server;
    handler_ = (TCPHandler *) (handler_generator());
    handler_->init(this, from_address);

}

void TCPConnection::WriteMsg(const std::string &msg) {
    //Event e(fd_, this);
    //e.set_write_callback<TCPConnection>(&TCPConnection::_WriteCallback);
    //IOLoop::Current()->AddEvent(e);
    send(fd_, &msg.front(), msg.size(), 0);

}

void TCPConnection::_ReadCallback(int fd, int data) {
    LOG_INFO << from_address_ << " Recv " << data << " bytes data";
    if (data == 0) {
        return;
    }
    std::string msg;
    msg.resize((size_t) data);
    recv(fd, &msg.front(), (size_t) data, 0);
    WriteMsg(handler_->Recv(msg));
}

void TCPConnection::_WriteCallback(int fd, int data) {
    throw IllegalFunctionError(to_string(fd) + " " + to_string(data));

}

void TCPConnection::_CloseCallback(int fd, int data) {
#if defined(DC_DEBUG)
    LOG_DEBUG << "fd" << fd << " Connection disconnected " << data;
#endif
    IOLoop::Current()->RemoveEvent(fd);
    tcp_server_->RemoveConnection(fd);
    close(fd);

}

}