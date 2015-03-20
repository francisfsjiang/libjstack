//
// Created by Neveralso on 15/3/19.
//

#include "TCPServer.h"


#include "Log.h"

namespace dc {


template<typename T>
void AddHandler(sa_family_t sock_type, sockaddr *sock_addr) {
    auto f = [=]() {
        return dynamic_cast<void *>(new T);
    };

    if (sa_family_t == PF_UNIX) {
        int sock_fd = socket(sock_type, SOCK_STREAM, 0);
        int ret = bind(sock_fd, sock_addr, sizeof(sock_addr));
        if (ret < 0) {
            LOG_CRITICAL << sock_addr->sa_data << " bind failed ." << errno;
            exit(0);
        }
        ret = bind()
    }
    else if (sa_family_t == PF_INET) {

    }

    port_route_map.
            insert(std::make_pair(port_num, f));
}

void TCPServer::AddListenEvent(sa_family_t sock_type, sockaddr *sock_addr) {

    //Event e();
    //dc::IOLoop::Current()->AddEvent()
}

}