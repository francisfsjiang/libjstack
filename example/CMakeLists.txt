
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++1y")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D ABATHUR_DEBUG")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

include_directories(include)


add_executable(tcp_echo_server tcp_echo_server.cpp)
add_executable(http_echo_server http_echo_server.cpp)
add_executable(http_proxy_server http_proxy_server.cpp)


target_link_libraries(tcp_echo_server  ${LIBS})
target_link_libraries(http_echo_server ${LIBS})
target_link_libraries(http_proxy_server ${LIBS})
