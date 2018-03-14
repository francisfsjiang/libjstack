#include <iostream>
#include "abathur/log.hpp"

using namespace std;
using namespace abathur;

int main() {
    LOG_DEBUG << "test debug";
    LOG_FATAL << "test fatal";
    LOG_INFO  << "test info";
    return 0;
}
