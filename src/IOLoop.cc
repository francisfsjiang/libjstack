//
// Created by Neveralso on 15/3/15.
//

#include "IOLoop.h"

#include <iostream>

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
    while (!quit_) {

    }

}

IOLoop::~IOLoop() {
    kIOLoopInstanceInThread = NULL;
}

}