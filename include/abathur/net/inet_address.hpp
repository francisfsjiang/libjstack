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

        const sockaddr* get_sock_addr() const;

        std::string to_string() const;
        std::string get_address_string() const;
        in_port_t get_port() const;

        sa_family_t get_protocol_family() const;
        socklen_t get_address_len() const ;
        const socklen_t* get_address_len_ptr() const;
    private:

        sockaddr_storage address_;
        socklen_t address_len_;

        int socket_type_;
    };

    const int k_MAX_INET_ADDRESS_LEN = 46;
}

#endif //_ABATHUR_INET_ADDRESS_HPP_