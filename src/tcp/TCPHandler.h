//
// Created by Neveralso on 15/3/20.
//

#ifndef _DEMONIAC_TCPHANDLER_H_
#define _DEMONIAC_TCPHANDLER_H_

#include <string>

namespace dc {

class TCPConnection;

class TCPHandler {
protected:
    TCPConnection* coon_;
    std::string from_;
public:
    TCPHandler();

    void _SetTcpConnection(TCPConnection* coon);
    void _SetFromAddress(const std::string from);

    virtual std::string Recv(const std::string msg) = 0;

    void Send(const std::string msg);
};

}

#endif //_DEMONIAC_TCPHANDLER_H_
