#ifndef _ABATHUR_TCP_TCPCONNECTION_H_
#define _ABATHUR_TCP_TCPCONNECTION_H_
#include <functional>
#include <queue>
#include <string>


namespace abathur {
namespace tcp {


class TCPHandler;

class TCPServer;

class TCPConnection{
private:
    int fd_;
    std::string from_address_ = "";
    TCPHandler *handler_ = nullptr;
    TCPServer *tcp_server_;
    std::queue<std::string> msg_queue_;

public:
    TCPConnection(const int &fd,
                  const std::string &from_address,
                  const std::function<void *()> &handler_generator,
                  TCPServer *tcp_server);

    void WriteMsg(const std::string &msg);

    void ReadCallback(int fd, int data);

    void WriteCallback(int fd, int data);

    void CloseCallback(int fd, int data);

};


}
}

#endif //_ABATHUR_TCPCONNECTION_H_
