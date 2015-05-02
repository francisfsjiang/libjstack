cmake_minimum_required(VERSION 2.8.4)
project(Demoniac)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++14")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D DC_DEBUG")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")


set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin_test)
set(LIBRARY_OUTPUT_PATH    ${PROJECT_SOURCE_DIR}/lib)

set(SRC_FILES
src/io_loop.cpp
src/event.cpp
src/log.cpp
src/poller/get_poller.cpp
src/tcp/tcp_handler.cpp
src/tcp/tcp_connection.cpp
src/tcp/tcp_server.cpp
)


if (${CMAKE_HOST_SYSTEM_NAME} MATCHES "Linux")
    message(${CMAKE_HOST_SYSTEM_NAME})
    set(SRC_FILES ${SRC_FILES} src/poller/epoll_poller.cpp)
else()
    message(${CMAKE_HOST_SYSTEM_NAME})
    set(SRC_FILES ${SRC_FILES} src/poller/kqueue_poller.cpp)
endif()

include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(demoniac STATIC ${SRC_FILES})

add_executable(ioloop_test     test/ioloop_test.cpp)
add_executable(ioloop_test2    test/ioloop_test2.cpp)
add_executable(log_test        test/log_test.cpp)
add_executable(tcp_echo_server test/tcp_echo_server.cpp)

target_link_libraries(ioloop_test     demoniac)
target_link_libraries(ioloop_test2    demoniac)
target_link_libraries(log_test        demoniac)
target_link_libraries(tcp_echo_server demoniac)

add_subdirectory(example)