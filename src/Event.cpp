//
// Created by Neveralso on 15/3/17.
//

#include "Event.h"

#include "util/error.h"

namespace dc {

Event::Event(int fd, void *obj_ptr) : fd_(fd), obj_ptr_(obj_ptr){
}

int Event::GetFD() const {
    return fd_;
}

template <typename T>
void Event::set_read_callback(void(T::*callback)(int, int)) {
    if (!obj_ptr_)
        throw IllegalFunctionError("Object not set");
    auto f = std::bind(obj_ptr_, callback, std::placeholders::_1, std::placeholders::_2);
    read_callback_ = [](int fd, int data) {
        f(fd, data);
    };
}

void Event::set_read_callback(callback_func callback) {
    read_callback_ = callback;
}

template <typename T>
void Event::set_write_callback(void(T::*callback)(int, int)) {
    auto f = std::bind(obj_ptr_, callback, std::placeholders::_1, std::placeholders::_2);
    write_callback_ = [](int fd, int data) {
        f(fd, data);
    };
}

void Event::set_write_callback(callback_func callback) {
    write_callback_ = callback;
}

template <typename T>
void Event::set_close_callback(void(T::*callback)(int, int)) {
    auto f = std::bind(obj_ptr_, callback, std::placeholders::_1, std::placeholders::_2);
    close_callback_ = [](int fd, int data) {
        f(fd, data);
    };
}

void Event::set_close_callback(callback_func callback) {
    close_callback_ = callback;
}


Event::~Event() {
}

void Event::exec_read_callback(int fd, int data) const {
    read_callback_(fd, data);
}

void Event::exec_write_callback(int fd, int data) const {
    write_callback_(fd, data);
}

void Event::exec_close_callback(int fd, int data) const {
    close_callback_(fd, data);
}

bool Event::has_write_callback() const {
    return !(write_callback_ == NULL);
}

bool Event::has_close_callback() const {
    return !(close_callback_ == NULL);
}

bool Event::has_read_callback() const {
    return !(read_callback_ == NULL);
}


}