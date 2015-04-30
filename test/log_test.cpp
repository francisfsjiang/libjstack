#include <iostream>
#include "Demoniac/Log.h"

using namespace std;

int main() {
    LOG_DEBUG << "test debug";
    LOG_CRITICAL << "test critical";
    LOG_INFO << "test info";
    return 0;
}