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
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-c++1z-extensions")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unknown-escape-sequence")
ELSEIF (CMAKE_BUILD_TYPE MATCHES RELEASE)
    message("Building in release mode.")

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

ENDIF ()

#set(CMAKE_CXX_FLAGS_DEBUG  "${CMAKE_CXX_FLAGS} -Wall")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++1z")


set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin_test)
set(LIBRARY_OUTPUT_PATH    ${PROJECT_SOURCE_DIR}/lib)

set(SRC_FILES
        src/io_loop.cpp
        src/log.cpp
        src/event.cpp
        src/channel.cpp
        src/event_processor.cpp
        src/poller/get_poller.cpp
        src/net/socket.cpp
        src/net/socket_handler.cpp
        src/net/socket_server.cpp
        src/net/inet_address.cpp
        src/http/async_http_client.cpp
        src/http/http_request.cpp
        src/http/http_response.cpp
        src/http/parser/http_parser.c
        src/util/buffer.cpp
        )

set(HEADER_FILES
        include/abathur/abathur.hpp
        include/abathur/io_loop.hpp
        include/abathur/log.hpp
        include/abathur/event.hpp
        include/abathur/channel.hpp
        include/abathur/error.hpp
        include/abathur/event_processor.hpp
        include/abathur/poller/get_poller.hpp
        include/abathur/poller/poller.hpp
        include/abathur/net/socket.hpp
        include/abathur/net/socket_handler.hpp
        include/abathur/net/socket_server.hpp
        include/abathur/net/inet_address.hpp
        include/abathur/http/async_http_client.hpp
        include/abathur/http/http_request.hpp
        include/abathur/http/http_response.hpp
        src/http/parser/http_parser.h
        include/abathur/util/buffer.hpp
        )


message("Building on ${CMAKE_HOST_SYSTEM_NAME} platform.")
if (${CMAKE_HOST_SYSTEM_NAME} MATCHES "Linux")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D ABATHUR_LINUX")
    set(SRC_FILES ${SRC_FILES} src/poller/epoll_poller.cpp)
    set(HEADER_FILES ${HEADER_FILES} src/poller/epoll_poller.hpp)
ELSEIF (${CMAKE_HOST_SYSTEM_NAME} MATCHES "Darwin")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D ABATHUR_DARWIN")
    set(SRC_FILES ${SRC_FILES} src/poller/kqueue_poller.cpp)
    set(HEADER_FILES ${HEADER_FILES} src/poller/kqueue_poller.hpp)
ELSEIF (${CMAKE_HOST_SYSTEM_NAME} MATCHES "Windows")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D ABATHUR_LINUX")
    set(SRC_FILES ${SRC_FILES} src/poller/iocp_poller.cpp)
endif ()

find_package(Boost REQUIRED COMPONENTS context coroutine)
find_package(Curl REQUIRED)

link_directories(${PROJECT_SOURCE_DIR}/lib)
link_directories(${BOOST_ROOT}/lib)

set(DEP_LIBS boost_coroutine-mt boost_context-mt curl)
set(LIBS abathur ${DEP_LIBS})

message("Building libraries: ${LIBS}")
message("Building flags: ${CMAKE_CXX_FLAGS}")

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${BOOST_ROOT}/include)

add_library(abathur STATIC ${SRC_FILES} )

set(CMAKE_MACOSX_RPATH ON)
add_library(abathur_dynamic SHARED ${SRC_FILES})
set_target_properties(abathur_dynamic PROPERTIES OUTPUT_NAME abathur)
target_link_libraries(abathur_dynamic ${DEP_LIBS})

#add_executable(ioloop_test     test/ioloop_test.cpp)
#add_executable(ioloop_test2    test/ioloop_test2.cpp)
add_executable(log_test        test/log_test.cpp)
add_executable(tcp_echo_server test/tcp_echo_server.cpp)
add_executable(http_echo_server test/http_echo_server.cpp)

#target_link_libraries(ioloop_test     ${LIBS})
#target_link_libraries(ioloop_test2    ${LIBS})
target_link_libraries(log_test         ${LIBS})
target_link_libraries(tcp_echo_server  ${LIBS})
target_link_libraries(http_echo_server ${LIBS})

#add_subdirectory(example)
