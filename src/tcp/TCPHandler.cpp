//
// Created by Neveralso on 15/3/20.
//

#include "TCPHandler.h"

#include "TCPConnection.h"

namespace dc {


TCPHandler::TCPHandler() {

}

void TCPHandler::Send(const std::string msg) {
    coon_->WriteMsg(msg);
}

void TCPHandler::init(TCPConnection *coon, const std::string from) {
    coon_ = coon;
    from_ = from;
}

}