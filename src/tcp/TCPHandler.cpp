//
// Created by Neveralso on 15/3/20.
//

#include "TCPHandler.h"
#include "TCPConnection.h"

#include <string>

namespace dc {


TCPHandler::TCPHandler() {

}

void TCPHandler::Send(const std::string msg) {
    coon_->WriteMsg(msg);
}

void TCPHandler::_SetFromAddress(const std::string from) {
    from_ = from;
}


void TCPHandler::_SetTcpConnection(TCPConnection *coon) {
    coon_ = coon;
}
}