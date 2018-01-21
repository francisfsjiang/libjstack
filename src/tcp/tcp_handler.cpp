#include "abathur/tcp/tcp_handler.h"

#include "abathur/tcp/tcp_connection.h"

namespace abathur {
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