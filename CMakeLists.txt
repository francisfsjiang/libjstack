cmake_minimum_required(VERSION 2.8.4)
project(Demoniac)



set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11 -pedantic -Wall -Werror -Wextra -D DC_DEBUG")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

set(SRC_FILE
src/IOLoop.cpp
src/Event.cpp
src/Log.cpp
#src/TCPServer.cpp
#src/TCPConnection.cpp
#src/TCPHandler.cpp
src/poller/GetPoller.cpp
src/util/error.cpp
)

if (${CMAKE_HOST_SYSTEM_NAME} MATCHES "Darwin")
    message(${CMAKE_HOST_SYSTEM_NAME})
    set(SRC_FILE ${SRC_FILE} src/poller/KqueuePoller.cpp)
elseif (${CMAKE_HOST_SYSTEM_NAME} MATCHES "Linux")
    message(${CMAKE_HOST_SYSTEM_NAME})
    set(SRC_FILE ${SRC_FILE} src/poller/EpollPoller.cpp)
endif()

add_library(demoniac STATIC ${SRC_FILE})


add_executable(ioloop_test test/ioloop_test.cc)
add_executable(ioloop_test2 test/ioloop_test2.cc)
add_executable(log_test test/log_test.cc)


target_link_libraries(ioloop_test demoniac)
target_link_libraries(log_test demoniac)
target_link_libraries(ioloop_test2 demoniac)