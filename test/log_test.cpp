#include <iostream>
#include "abathur/log.hpp"

using namespace std;
using namespace abathur;

int main() {
    LOG_DEBUG << "test debug";
    LOG_CRITICAL << "test critical";
    LOG_INFO << "test info";
    return 0;
}