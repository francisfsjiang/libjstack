cmake_minimum_required(VERSION 2.8.4)
project(Demoniac)



set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++1y -pedantic -Wall -Werror -Wextra -D DC_DEBUG")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

set(SRC_FILE
src/IOLoop.cc
src/Event.cc
src/Log.cc
src/poller/GetPoller.cc
src/util/error.cc
)

if (${CMAKE_HOST_SYSTEM_NAME} MATCHES "Darwin")
    message(${CMAKE_HOST_SYSTEM_NAME})
    set(SRC_FILE ${SRC_FILE} src/poller/KqueuePoller.cc)
elseif (${CMAKE_HOST_SYSTEM_NAME} MATCHES "Linux")
    message(${CMAKE_HOST_SYSTEM_NAME})
    set(SRC_FILE ${SRC_FILE} src/poller/EpollPoller.cc)
endif()

add_library(demoniac STATIC ${SRC_FILE} src/poller/GetPoller.cc src/poller/GetPoller.h src/TCPServer.cc src/TCPServer.h src/TCPConnection.cc src/TCPConnection.h)


add_executable(ioloop_test test/ioloop_test.cc)
add_executable(log_test test/log_test.cc)


target_link_libraries(ioloop_test demoniac)
target_link_libraries(log_test demoniac)