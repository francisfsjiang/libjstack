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
    while (!quit_) {

    }

}

IOLoop::~IOLoop() {
    kIOLoopInstanceInThread = NULL;
}

}