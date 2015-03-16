//
// Created by Neveralso on 15/3/15.
//

#include "IOLoop.hpp"

using namespace dc;

__thread IOLoop* _IOLoopInstanceInThread = NULL;


IOLoop::IOLoop() {
    if (_IOLoopInstanceInThread != NULL) {
        _instance = _IOLoopInstanceInThread;
    }
    else {
        _IOLoopInstanceInThread = this;

    }
}