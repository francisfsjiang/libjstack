#include "abathur/event.hpp"

#include <iostream>

namespace abathur {
    Event::Event(int fd) {
        fd_ = fd;
        read_ = write_ = close_ = false;
    }
    Event::Event(int fd, bool readable, bool writable, bool closeable):
            fd_(fd), read_(readable), write_(writable), close_(closeable) {

    }
    bool Event::Readable() const {
        return read_;
    }
    bool Event::Writable() const {
        return write_;
    }
    bool Event::Closeable() const {
        return close_;
    }

    int Event::GetFD() const {
        return fd_;
    }

    void Event::setReadable(bool yes) {
        read_ = yes;
    }
    void Event::setWriteable(bool yes) {
        write_ = yes;
    }
    void Event::setCloseable(bool yes) {
        close_ = yes;
    }
}