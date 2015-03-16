cmake_minimum_required(VERSION 2.8.4)
project(Demoniac)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)


set(SRC_FILE
src/IOLoop.hpp
src/IOLoop.cpp
src/util/error.hpp
src/util/error.cpp
src/util/noncopyable.hpp
)

add_executable(ioloop_test test/ioloop_test.cpp ${SRC_FILE})
