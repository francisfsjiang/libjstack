//
// Created by Neveralso on 15/3/17.
//


#include "demoniac/event_callback.h"

#include "demoniac/util/error.h"

namespace demoniac {

EventCallback::EventCallback(){ }

void EventCallback::SetReadCallback(CallbackFunction read_callback) {
    read_callback_ =  read_callback;
}

bool EventCallback::HasReadCallback() const {
    return read_callback_? true: false;
}

void EventCallback::ExecReadCallback(const int& fd, const int& data) const {
    read_callback_(fd, data);
}

void EventCallback::SetWriteCallback(CallbackFunction write_callback) {
    write_callback_ = write_callback;
}

bool EventCallback::HasWriteCallback() const {
    return write_callback_? true: false;
}

void EventCallback::ExecWriteCallback(const int& fd, const int& data) const {
    write_callback_(fd, data);
}

void EventCallback::SetErrorCallback(CallbackFunction error_callback) {
    error_callback_ = error_callback;
}

bool EventCallback::HasErrorCallback() const {
    return error_callback_? true: false;
}

void EventCallback::ExecErrorCallback(const int& fd, const int& data) const {
    error_callback_(fd, data);
}

void EventCallback::SetCloseCallback(CallbackFunction close_callback) {
    close_callback_ = close_callback;
}

bool EventCallback::HasCloseCallback() const {
    return close_callback_? true: false;
}

void EventCallback::ExecCloseCallback(const int& fd, const int& data) const {
    close_callback_(fd, data);
}

}