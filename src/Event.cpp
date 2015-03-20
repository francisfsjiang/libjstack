//
// Created by Neveralso on 15/3/17.
//

#include "Event.h"

namespace dc {

Event::Event(int fd) : fd_(fd) {
}

int Event::GetFD() const {
    return fd_;
}

void Event::set_read_call_back(std::function<void(int, int)> call_back) {
    read_call_back_ = call_back;
}

void Event::set_write_call_back(std::function<void(int, int)> call_back) {
    write_call_back_ = call_back;
}

Event::~Event() {
}

void Event::exec_read_call_back(int fd, int data) {
    read_call_back_(fd,data);
}

void Event::exec_write_call_back(int fd, int data) {
    write_call_back_(fd,data);
}
}