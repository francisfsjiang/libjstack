//
// Created by Neveralso on 15/3/19.
//

#include "TCPConnection.h"

#include "../IOLoop.h"
#include "../Log.h"

namespace dc {


TCPConnection::TCPConnection(const int& fd,
                             const std::string& from_address,
                             std::function<void *()> handler_generator) {
    fd_ = fd;
    from_address_ = from_address;
    handler_ = (TCPHandler*)(handler_generator());
    handler_->_SetTcpConnection(this);
    handler_->_SetFromAddress(from_address);

}

void TCPConnection::_ReadEvent(int fd, int data) {
    LOG_INFO << from_address_ << " Recv " << data << " bytes data";
    std::string msg;
    msg.resize((size_t)data);
    recv(fd, &msg.front(), (size_t)data, 0);
    _WriteMsg(handler_->Recv(msg));
}

void TCPConnection::_WriteEvent(int fd, int data) {
    LOG_INFO << fd << from_address_ << " Send " << data << " bytes data ";
    //Send(fd, )

}

void TCPConnection::_WriteMsg(const std::string& msg) {
    //Event e(fd_, this);
    //e.set_write_callback<TCPConnection>(&TCPConnection::_WriteEvent);
    //IOLoop::Current()->AddEvent(e);
    send(fd_, &msg.front(), msg.size(), 0);

}
}