cmake_minimum_required(VERSION 2.8.4)
project(Demoniac)



set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

set(SRC_FILE
src/IOLoop.h
src/IOLoop.cc
src/Event.h
src/Event.h
src/util/error.h
src/util/error.cc
src/util/noncopyable.h
)

add_executable(ioloop_test test/ioloop_test.cc ${SRC_FILE} src/Event.cc src/Event.h src/poller/Poller.cc src/poller/Poller.h src/poller/EpollPoller.cc src/poller/EpollPoller.h src/poller/KqueuePoller.cc src/poller/KqueuePoller.h)
