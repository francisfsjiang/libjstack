//
// Created by Neveralso on 15/3/15.
//

#include "IOLoop.h"

#include "Log.h"

namespace dc {

__thread IOLoop* kIOLoopInstanceInThread = NULL;

IOLoop::IOLoop() {
    if (kIOLoopInstanceInThread != NULL) {
        instance_ = kIOLoopInstanceInThread;
    }
    else {
        kIOLoopInstanceInThread = this;
        instance_ = this;
    }
}

void IOLoop::Loop() {
    LOG_INFO << "Loop start.";
    int count=0;
    while (!quit_) {
        LOG_DEBUG << "Looped " <<count++;
    }

}

IOLoop::~IOLoop() {
    kIOLoopInstanceInThread = NULL;
}

void IOLoop::AddEvent(const Event &e) {
    events_list_.push_back(e);
}
}