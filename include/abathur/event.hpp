#ifndef _ABATHUR_EVENT_HPP_
#define _ABATHUR_EVENT_HPP_

#include <iostream>

namespace abathur {
    enum EVENT_FLAG{
        EF_READ = 1,
        EF_WRITE = 2,
        EF_CLOSE = 4,
        EF_ALL = 7
    };

    class Event {
    private:
        int fd_;
        uint filter_;

    public:

        Event(int);
        Event(int, uint);

        int get_fd() const;
        int get_filter() const;

        bool readable() const;
        bool writable() const;
        bool closeable() const;

        void set_readable(bool);
        void set_writable(bool);
        void set_closeable(bool);
    };
}


#endif //_ABATHUR_EVENT_HPP_
