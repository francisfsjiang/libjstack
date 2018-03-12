#ifndef _ABATHUR_EVENT_HPP_
#define _ABATHUR_EVENT_HPP_


namespace abathur {
    class Event {
    private:
        int fd_;
        bool read_, write_, close_;
    public:
        Event(int);
        Event(int, bool, bool, bool);

        int GetFD() const;

        bool Readable() const;
        bool Writable() const;
        bool Closeable() const;

        void setReadable(bool);
        void setWriteable(bool);
        void setCloseable(bool);
    };
}


#endif //_ABATHUR_EVENT_HPP_
