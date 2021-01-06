#ifndef LIBJSTACK_TYPES_HPP
#define LIBJSTACK_TYPES_HPP

#include <vector>
#include <string>

namespace libjstack {

    using Bytes = std::vector<std::byte>;

    std::string bytes_to_hex_string(Bytes);

    Bytes string_to_bytes(std::string);

}

#endif //LIBJSTACK_TYPES_HPP
