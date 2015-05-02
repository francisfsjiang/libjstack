
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++1y")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D DC_DEBUG")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

include_directories(include)
add_executable(echo_server     echo_server.cpp)

target_link_libraries(echo_server     demoniac)