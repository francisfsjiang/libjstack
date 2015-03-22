cmake_minimum_required(VERSION 2.8.4)
project(Demoniac)



set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11 -D DC_DEBUG")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -Wall -Werror -Wextra")


set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH    ${PROJECT_BINARY_DIR}/lib)

set(SRC_FILES
src/IOLoop.cpp
src/Event.cpp
src/Log.cpp
src/poller/GetPoller.cpp
src/tcp/TCPHandler.cpp
src/tcp/TCPConnection.cpp
src/tcp/TCPServer.cpp

)


if (${CMAKE_HOST_SYSTEM_NAME} MATCHES "Linux")
    message(${CMAKE_HOST_SYSTEM_NAME})
    set(SRC_FILES ${SRC_FILES} src/poller/EpollPoller.cpp)
else()
    message(${CMAKE_HOST_SYSTEM_NAME})
    set(SRC_FILES ${SRC_FILES} src/poller/KqueuePoller.cpp)
endif()

add_library(demoniac STATIC ${SRC_FILES})

add_executable(ioloop_test     test/ioloop_test.cpp)
add_executable(ioloop_test2    test/ioloop_test2.cpp)
add_executable(log_test        test/log_test.cpp)


target_link_libraries(ioloop_test     demoniac)
target_link_libraries(ioloop_test2    demoniac)
target_link_libraries(log_test        demoniac)

#target_link_libraries(tcp_echo_server demoniac)


add_executable(tcp_echo_server test/tcp_echo_server.cpp ${SRC_FILES})