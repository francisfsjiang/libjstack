//
// Created by Neveralso on 15/3/20.
//

#ifndef _DEMONIAC_TCPHANDLER_H_
#define _DEMONIAC_TCPHANDLER_H_

#include <string>

namespace dc {

class TCPHandler {
private:

public:
    TCPHandler();

    virtual std::string recv(const std::string msg) = 0;

    virtual std::string send(const std::string msg) = 0;
};

}

#endif //_DEMONIAC_TCPHANDLER_H_
