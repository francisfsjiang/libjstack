#ifndef _ABATHUR_TCP_TCPHANDLER_H_
#define _ABATHUR_TCP_TCPHANDLER_H_

#include <string>

namespace abathur {
namespace tcp {


class TCPConnection;

class TCPHandler {
protected:
    TCPConnection *coon_;
    std::string from_;
public:
    TCPHandler();

    void init(TCPConnection *coon, const std::string from);

    virtual std::string Recv(const std::string msg) = 0;

    void Send(const std::string msg);
};

}
}

#endif //_ABATHUR_TCPHANDLER_H_
