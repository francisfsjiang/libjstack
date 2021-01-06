#include "crypto/md5.hpp"

#include <openssl/md5.h>

namespace libjstack::crypto {
//    std::string md5(const char* data, size_t size) {
//        unsigned char md[16];
//        std::ostringstream os;
//        MD5(reinterpret_cast<const unsigned char*>(data), size, md);
//        os << std::setw(2) << std::setfill('0') << std::hex << std::uppercase;
//        for (int i = 0; i < 16; ++i) {
//            os << std::setw(2) << static_cast<int>(md[i]);
//        }
//        return os.str();
//    }

    libjstack::Bytes md5(libjstack::Bytes data)
    {
        Bytes result = Bytes(16);
        MD5(reinterpret_cast<const unsigned char*>(data.data()), data.size(), reinterpret_cast<unsigned char*>(result.data()));
        return result;
    }

}