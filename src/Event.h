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
    typedef std::function<void(int, int)> callback_func;
    void *obj_ptr_ = NULL;
    callback_func read_callback_ = NULL;
    callback_func write_callback_ = NULL;
    callback_func close_callback_ = NULL;
public:
    Event(int fd, void *obj_ptr);

    ~Event();

    int GetFD() const;

    template <typename T>
    void set_read_callback(void(T::*callback)(int, int));

    void set_read_callback(callback_func callback);

    template <typename T>
    void set_write_callback(void(T::*callback)(int, int));

    void set_write_callback(callback_func callback);

    template <typename T>
    void set_close_callback(void(T::*callback)(int, int));

    void set_close_callback(callback_func callback);

    bool has_write_callback() const;

    bool has_close_callback() const;

    bool has_read_callback() const;

    void exec_read_callback(int fd, int data) const;

    void exec_write_callback(int fd, int data) const;

    void exec_close_callback(int fd, int data) const;
};

}

#endif //_DEMONIAC_EVENT_H_
