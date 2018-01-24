cmake_minimum_required(VERSION 2.8)
project(Abathur)

IF (CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE "DEBUG")
ENDIF()

IF (USE_LIBC++)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
ENDIF()

IF (CMAKE_BUILD_TYPE MATCHES DEBUG)
    message("Building in debug mode.")

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D ABATHUR_DEBUG")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")
ELSEIF (CMAKE_BUILD_TYPE MATCHES RELEASE)
    message("Building in release mode.")

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

ENDIF ()


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++1z")


set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin_test)
set(LIBRARY_OUTPUT_PATH    ${PROJECT_SOURCE_DIR}/lib)

set(SRC_FILES
src/io_loop.cpp
src/event_callback.cpp
src/log.cpp
src/poller/get_poller.cpp
src/tcp/tcp_handler.cpp
src/tcp/tcp_connection.cpp
src/tcp/tcp_server.cpp
)


message("Building on ${CMAKE_HOST_SYSTEM_NAME} platform.")
if (${CMAKE_HOST_SYSTEM_NAME} MATCHES "Linux")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D ABATHUR_LINUX")
    set(SRC_FILES ${SRC_FILES} src/poller/epoll_poller.cpp)
ELSEIF (${CMAKE_HOST_SYSTEM_NAME} MATCHES "Darwin")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D ABATHUR_DARWIN")
    set(SRC_FILES ${SRC_FILES} src/poller/kqueue_poller.cpp)
ELSEIF (${CMAKE_HOST_SYSTEM_NAME} MATCHES "Darwin")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D ABATHUR_LINUX")
    set(SRC_FILES ${SRC_FILES} src/poller/kqueue_poller.cpp)
endif ()

message("Building flags: ${CMAKE_CXX_FLAGS}")

include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(abathur STATIC ${SRC_FILES})

add_executable(ioloop_test     test/ioloop_test.cpp)
add_executable(ioloop_test2    test/ioloop_test2.cpp)
add_executable(log_test        test/log_test.cpp)
add_executable(tcp_echo_server test/tcp_echo_server.cpp)

target_link_libraries(ioloop_test     abathur)
target_link_libraries(ioloop_test2    abathur)
target_link_libraries(log_test        abathur)
target_link_libraries(tcp_echo_server abathur)

add_subdirectory(example)