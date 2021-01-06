#include "types.hpp"

#include <algorithm>
#include <sstream>
#include <string>
#include <iomanip>

namespace libjstack {
    std::string bytes_to_hex_string(Bytes bytes)
    {
        std::ostringstream os;
        os << std::setw(2) << std::setfill('0') << std::hex << std::uppercase;
        for (int i = 0; i < 16; ++i) {
            os << std::setw(2) << static_cast<int>(bytes[i]);
        }
        return os.str();
    }

    Bytes string_to_bytes(std::string str)
    {
//        Bytes result;
//        std::vector<std::byte> gpsValueArray(str.size() + 1);
//        std::transform(str.begin(), str.end(), result.begin(),
//                       [] (char c) { return std::byte(c); });
        return Bytes((std::byte*)str.data(), (std::byte*)str.data() + str.size());
//        return result;
    }
}