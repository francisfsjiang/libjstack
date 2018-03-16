#ifndef _ABATHUR_EVENT_HPP_
#define _ABATHUR_EVENT_HPP_


namespace abathur {
    enum EVENT_FLAG{
        EF_READ = 1,
        EF_WRITE = 2,
        EF_CLOSE = 4
    };

    class Event {
    private:
        int fd_;
        int filter_;

    public:

        Event(int);
        Event(int, int);

        int GetFD() const;
        int GetFilter() const;

        bool Readable() const;
        bool Writable() const;
        bool Closeable() const;

        void setReadable(bool);
        void setWritable(bool);
        void setCloseable(bool);
    };
}


#endif //_ABATHUR_EVENT_HPP_
