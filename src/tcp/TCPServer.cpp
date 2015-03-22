//
// Created by Neveralso on 15/3/19.
//

#include "TCPServer.h"

#include <string>



namespace dc {

TCPServer::TCPServer() {

}

void TCPServer::CreateConnection(int fd, int data) {

#if defined(DC_DEBUG)
    LOG_DEBUG << fd << "has" << data << "connections";
#endif

    sockaddr sock_addr;
    socklen_t sock_addr_len;

    for (int i = 0; i < data; ++i) {

        int coon_fd = accept(fd, &sock_addr, &sock_addr_len);
        TCPConnection *coon;

        string from_address;
        if (sock_addr.sa_family == PF_UNIX) {
            from_address += sock_addr.sa_data;
        }
        else {
            from_address += inet_ntoa(((sockaddr_in *) &sock_addr)->sin_addr);
            from_address += std::to_string(((sockaddr_in *) &sock_addr)->sin_port);
        }

        LOG_INFO << fd
        << "Incoming connection from "
        << from_address;

        coon = new TCPConnection(coon_fd,
                                 from_address,
                                 route_map_[fd]);

        dc::Event e(coon_fd, coon);
        e.set_read_callback<TCPConnection>(&TCPConnection::_ReadEvent);
        e.set_close_callback<TCPConnection>(&TCPConnection::_WriteEvent);
        dc::IOLoop::Current()->AddEvent(e);

        connection_poll_.insert(make_pair(coon_fd, coon));


    }

}

//void TCPServer::CloseConnection(int fd, int data) {
//#if defined(DC_DEBUG)
//    LOG_DEBUG << fd << "connection " << data << "connections";
//#endif
//
//
//}

}