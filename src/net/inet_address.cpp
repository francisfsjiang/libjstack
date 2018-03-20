#include "abathur/net/inet_address.hpp"

#include <stdexcept>
#include <cstring>
#include <regex>
#include <string>

#include <arpa/inet.h>
#include <sys/un.h>

#include "abathur/log.hpp"
#include "abathur/error.hpp"

namespace abathur::net {

    static std::regex re_ipv4("^([01]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])\\.([01]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])\\.([01]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])\\.([01]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])$");

    static std::regex re_ipv6("(([0-9a-fA-F]{1,4}:){7,7}[0-9a-fA-F]{1,4}|([0-9a-fA-F]{1,4}:){1,7}:|([0-9a-fA-F]{1,4}:){1,6}:[0-9a-fA-F]{1,4}|([0-9a-fA-F]{1,4}:){1,5}(:[0-9a-fA-F]{1,4}){1,2}|([0-9a-fA-F]{1,4}:){1,4}(:[0-9a-fA-F]{1,4}){1,3}|([0-9a-fA-F]{1,4}:){1,3}(:[0-9a-fA-F]{1,4}){1,4}|([0-9a-fA-F]{1,4}:){1,2}(:[0-9a-fA-F]{1,4}){1,5}|[0-9a-fA-F]{1,4}:((:[0-9a-fA-F]{1,4}){1,6})|:((:[0-9a-fA-F]{1,4}){1,7}|:)|fe80:(:[0-9a-fA-F]{0,4}){0,4}%[0-9a-zA-Z]{1,}|::(ffff(:0{1,4}){0,1}:){0,1}((25[0-5]|(2[0-4]|1{0,1}[0-9]){0,1}[0-9])\\.){3,3}(25[0-5]|(2[0-4]|1{0,1}[0-9]){0,1}[0-9])|([0-9a-fA-F]{1,4}:){1,4}:((25[0-5]|(2[0-4]|1{0,1}[0-9]){0,1}[0-9])\\.){3,3}(25[0-5]|(2[0-4]|1{0,1}[0-9]){0,1}[0-9]))");

    const int k_MAX_INET_PORT_LEN = 6;

    InetAddress::InetAddress(const char *addr) {
        memset(&address_, 0, sizeof(address_));
        sockaddr_un* un_ptr = reinterpret_cast<sockaddr_un*>(&address_);
        un_ptr -> sun_family = AF_UNIX;
        std::strcpy(un_ptr -> sun_path, addr);
        address_len_ = sizeof(sockaddr_un);
        socket_type_ = AF_UNIX;
    }

    InetAddress::InetAddress(const char* addr, const in_port_t& port) {
        memset(&address_, 0, sizeof(address_));
        if (std::strcmp(addr, "localhost") == 0) {
            sockaddr_in *in_ptr = reinterpret_cast<sockaddr_in*>(&address_);
            in_ptr -> sin_family = AF_INET;
            in_ptr -> sin_port = htons(port);
            address_len_ = sizeof(sockaddr_in);
            socket_type_ = AF_INET;
        }
        else if (std::regex_match(addr, re_ipv4)) {
            sockaddr_in *in_ptr = reinterpret_cast<sockaddr_in*>(&address_);
            int ret = inet_pton(AF_INET, addr, &in_ptr->sin_addr.s_addr);
            if (ret != 1) {
                LOG_ERROR << "Illegal IP Address " <<  addr;
            }
            in_ptr -> sin_family = AF_INET;
            in_ptr -> sin_port = htons(port);
            address_len_ = sizeof(sockaddr_in);
            socket_type_ = AF_INET;
        }
        else if (std::regex_match(addr, re_ipv6)) {
            sockaddr_in6 *in6_ptr = reinterpret_cast<sockaddr_in6*>(&address_);
            int ret = inet_pton(AF_INET6, addr, &in6_ptr->sin6_addr);
            if (ret != 1) {
                LOG_ERROR << "Illegal IP Address " <<  addr;
            }
            in6_ptr -> sin6_family = AF_INET6;
            in6_ptr -> sin6_port = htons(port);
            address_len_ = sizeof(sockaddr_in6);
            socket_type_ = AF_INET6;
        }
        else {
            LOG_ERROR << "Illegal IP Address " <<  addr;
        }
    }

    InetAddress::InetAddress(const in_port_t& port) {
        memset(&address_, 0, sizeof(address_));
        sockaddr_in6 *in6_ptr = reinterpret_cast<sockaddr_in6*>(&address_);
        in6_ptr -> sin6_family = AF_INET6;
        in6_ptr -> sin6_addr = in6addr_any;
        in6_ptr -> sin6_port = port;
        address_len_ = sizeof(sockaddr_in6);
        socket_type_ = AF_INET6;
    }

    InetAddress::InetAddress(const sockaddr* sock_addr, socklen_t sock_len) {
        memcpy(&address_, sock_addr, sock_len);
        address_len_ = sock_len;
    }

    const sockaddr* InetAddress::get_sock_addr() const{
        return reinterpret_cast<const sockaddr*>(&address_);
    }

    std::string InetAddress::to_string() const{
        char buf[k_MAX_INET_ADDRESS_LEN + k_MAX_INET_PORT_LEN];
        if (address_.ss_family == AF_INET) {
            const sockaddr_in *in_ptr = reinterpret_cast<const sockaddr_in*>(&address_);
            inet_ntop(address_.ss_family, &in_ptr->sin_addr, buf, sizeof(buf));
            sprintf(buf + k_MAX_INET_ADDRESS_LEN, ":%d", ntohs(in_ptr->sin_port));
        }
        else {
            const sockaddr_in6 *in6_ptr = reinterpret_cast<const sockaddr_in6*>(&address_);
            buf[0] = '[';
            inet_ntop(address_.ss_family, &in6_ptr->sin6_addr, buf+1, sizeof(buf));
            sprintf(buf + k_MAX_INET_ADDRESS_LEN, "]:%d", ntohs(in6_ptr->sin6_port));
        }
        return std::string(buf) + std::string(buf+k_MAX_INET_ADDRESS_LEN);
    }

    std::string InetAddress::get_address_string() const{
        char buf[k_MAX_INET_ADDRESS_LEN];
        if (address_.ss_family == AF_INET) {
            const sockaddr_in *in_ptr = reinterpret_cast<const sockaddr_in*>(&address_);
            inet_ntop(address_.ss_family, &in_ptr->sin_addr, buf, sizeof(buf));
        }
        else {
            const sockaddr_in6 *in6_ptr = reinterpret_cast<const sockaddr_in6*>(&address_);
            inet_ntop(address_.ss_family, &in6_ptr->sin6_addr, buf, sizeof(buf));
        }
        return std::string(buf);
    }

    in_port_t InetAddress::get_port() const {
        if (address_.ss_family == AF_INET) {
            const sockaddr_in *in_ptr = reinterpret_cast<const sockaddr_in*>(&address_);
            return ntohs(in_ptr->sin_port);
        }
        else {
            const sockaddr_in6 *in6_ptr = reinterpret_cast<const sockaddr_in6*>(&address_);
            return ntohs(in6_ptr->sin6_port);
        }
    }

    sa_family_t InetAddress::get_protocol_family() const{
        return reinterpret_cast<const sockaddr_in6*>(&address_) -> sin6_family;
    }

    socklen_t InetAddress::get_address_len() const{
        return address_len_;
    }

    const socklen_t * InetAddress::get_address_len_ptr() const{
        return &address_len_;
    }

}
