//
// Created by Neveralso on 15/3/19.
//

#ifndef _DEMONIAC_TCPSERVER_H_
#define _DEMONIAC_TCPSERVER_H_

#include <map>

#include "IOLoop.h"
#include "TCPHandler.h"
#include "util/noncopyable.h"

namespace dc {

class TCPServer: noncopyable {
private:
    std::map<int, TCPHandler> handler_map;
public:

};

}

#endif //_DEMONIAC_TCPSERVER_H_
