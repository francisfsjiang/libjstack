cmake_minimum_required(VERSION 2.8.4)
project(Demoniac)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++1y -pedantic -Wall -Werror -Wextra")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

set(SRC_FILE
src/IOLoop.cc
src/poller/KqueuePoller.cc
src/poller/EpollPoller.cc
src/util/error.cc
)

add_executable(ioloop_test test/ioloop_test.cc ${SRC_FILE})
