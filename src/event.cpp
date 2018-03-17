#include "abathur/event.hpp"


namespace abathur {
    Event::Event(int fd) {
        fd_ = fd;
        filter_ = 0;
    }
    Event::Event(int fd, uint filter):
            fd_(fd), filter_(filter){

    }
    bool Event::Readable() const {
        return static_cast<bool>(filter_ & EF_READ);
    }
    bool Event::Writable() const {
        return static_cast<bool>(filter_ & EF_WRITE);
    }
    bool Event::Closeable() const {
        return static_cast<bool>(filter_ & EF_CLOSE);
    }

    int Event::GetFD() const {
        return fd_;
    }

    void Event::setReadable(bool on) {
        if (on)
            filter_ |= EF_READ;
        else
            filter_ &= ~EF_READ;
    }
    void Event::setWritable(bool on) {
        if (on)
            filter_ |= EF_WRITE;
        else
            filter_ &= ~EF_WRITE;
    }
    void Event::setCloseable(bool on) {
        if (on)
            filter_ |= EF_CLOSE;
        else
            filter_ &= ~EF_CLOSE;
    }
}