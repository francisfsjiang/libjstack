//
// Created by Neveralso on 15/3/20.
//

#include "demoniac/tcp/tcp_handler.h"

#include "demoniac/tcp/tcp_connection.h"

namespace demoniac {
namespace tcp {


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
}