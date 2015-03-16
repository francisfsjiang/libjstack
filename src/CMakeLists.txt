set(SRC_FILE
IOLoop.hpp
IOLoop.cpp
util/error.hpp
util/error.cpp
util/noncopyable.hpp
)

#subdirs(util)

add_executable(ioloop_test ioloop_test.cpp ${SRC_FILE})