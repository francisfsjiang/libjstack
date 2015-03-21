//
// Created by Neveralso on 15/3/17.
//

#include <Python/Python.h>
#include "Event.h"

namespace dc {

Event::Event(int fd,
        cb_func read_callback,
        cb_func write_callback,
        cb_func close_callback) : fd_(fd),
                                  read_callback_(read_callback),
                                  write_callback_(write_callback),
                                  close_callback_(close_callback) {
}

int Event::GetFD() const {
    return fd_;
}

void Event::set_read_callback(std::function<void(int, int)> callback) {
    read_callback_ = callback;
}

void Event::set_write_callback(std::function<void(int, int)> callback) {
    write_callback_ = callback;
}

void Event::set_close_callback(std::function<void(int, int)> callback) {
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