#ifndef _ABATHUR_INET_ADDRESS_HPP_
#define _ABATHUR_INET_ADDRESS_HPP_

#include <string>

#include <netinet/in.h>
#include <sys/socket.h>


namespace abathur::net {

    class InetAddress {
    public:
        InetAddress(const char*);

        InetAddress(const char*, const in_port_t&);

        InetAddress(const in_port_t &);

        InetAddress(const sockaddr*, socklen_t);

        InetAddress(const InetAddress&) = default;
        InetAddress& operator=(const InetAddress&) = default;

        const sockaddr* getSockAddrPtr() const;

        std::string toString() const;
        std::string getAddrString() const;
        in_port_t getPort() const;

        sa_family_t getProtocolFamily() const;
        socklen_t getAddressLen() const ;
        const socklen_t* getAddressLenPtr() const;
    private:

        sockaddr_storage address_;
        socklen_t address_len_;

    };

    const int k_MAX_INET_ADDRESS_LEN = 46;
}

#endif //_ABATHUR_INET_ADDRESS_HPP_