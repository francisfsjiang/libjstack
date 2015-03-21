//
// Created by Neveralso on 15/3/17.
//

#ifndef _DEMONIAC_EVENT_H_
#define _DEMONIAC_EVENT_H_

#include <functional>

namespace dc {

class Event {
private:
    int fd_ = -1;
    typedef std::function<void(int, int)> cb_func;
    cb_func read_callback_ = NULL;
    cb_func write_callback_ = NULL;
    cb_func close_callback_ = NULL;
public:
    Event(int fd,
            cb_func read_callback,
            cb_func write_callback,
            cb_func close_callback);

    ~Event();

    int GetFD() const;

    void set_read_callback(std::function<void(int, int)> callback);

    void set_write_callback(std::function<void(int, int)> callback);

    void set_close_callback(std::function<void(int, int)> callback);

    bool has_write_callback() const;

    bool has_close_callback() const;

    bool has_read_callback() const;

    void exec_read_callback(int fd, int data) const;

    void exec_write_callback(int fd, int data) const;

    void exec_close_callback(int fd, int data) const;
};

}

#endif //_DEMONIAC_EVENT_H_
