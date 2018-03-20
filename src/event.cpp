#include "abathur/event.hpp"


namespace abathur {
    Event::Event(int fd) {
        fd_ = fd;
        filter_ = 0;
    }
    Event::Event(int fd, uint filter):
            fd_(fd), filter_(filter){

    }
    bool Event::readable() const {
        return static_cast<bool>(filter_ & EF_READ);
    }
    bool Event::writable() const {
        return static_cast<bool>(filter_ & EF_WRITE);
    }
    bool Event::closeable() const {
        return static_cast<bool>(filter_ & EF_CLOSE);
    }

    int Event::get_fd() const {
        return fd_;
    }

    void Event::set_readable(bool on) {
        if (on)
            filter_ |= EF_READ;
        else
            filter_ &= ~EF_READ;
    }
    void Event::set_writable(bool on) {
        if (on)
            filter_ |= EF_WRITE;
        else
            filter_ &= ~EF_WRITE;
    }
    void Event::set_closeable(bool on) {
        if (on)
            filter_ |= EF_CLOSE;
        else
            filter_ &= ~EF_CLOSE;
    }
}