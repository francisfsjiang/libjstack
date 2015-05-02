//
// Created by Neveralso on 15/3/17.
//


#include "demoniac/event.h"

#include "demoniac/util/error.h"
#include "demoniac/util/event_handler.h"

namespace demoniac {


Event::Event(int fd, util::EventHandler *obj_ptr) : fd_(fd), handler_ptr_(obj_ptr) {
}

int Event::GetFD() const {
    return fd_;
}

void Event::set_read_callback(callback_func callback) {
    read_callback_ = callback;
}

void Event::set_read_callback() {
    if (!handler_ptr_)
        throw util::IllegalFunctionError("Object not set");
    has_read_callback_ = true;
}

void Event::set_write_callback(callback_func callback) {
    write_callback_ = callback;
}

void Event::set_write_callback() {
    if (!handler_ptr_)
        throw util::IllegalFunctionError("Object not set");
    has_write_callback_ = true;
}

void Event::set_close_callback(callback_func callback) {
    close_callback_ = callback;
}

void Event::set_close_callback() {
    if (!handler_ptr_)
        throw util::IllegalFunctionError("Object not set");
    has_close_callback_ = true;
}

Event::~Event() {
}

void Event::exec_read_callback(int fd, int data) const {
    if (handler_ptr_) {
        handler_ptr_->_ReadCallback(fd, data);
    }
    else {
        read_callback_(fd, data);
    }
}

void Event::exec_write_callback(int fd, int data) const {
    if (handler_ptr_) {
        handler_ptr_->_WriteCallback(fd, data);
    }
    else {
        read_callback_(fd, data);
    }
}

void Event::exec_close_callback(int fd, int data) const {
    if (handler_ptr_) {
        handler_ptr_->_CloseCallback(fd, data);
    }
    else {
        read_callback_(fd, data);
    }
}

bool Event::has_close_callback() const {
    return !(close_callback_ == NULL && !has_close_callback_);
}

bool Event::has_write_callback() const {
    return !(write_callback_ == NULL && !has_write_callback_);
}

bool Event::has_read_callback() const {
    return !(read_callback_ == NULL && !has_read_callback_);
}


}