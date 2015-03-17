//
// Created by Neveralso on 15/3/15.
//

#include "IOLoop.h"

#include <iostream>
#include <pthread.h>

using namespace std;
using namespace dc;

__thread IOLoop* _IOLoopInstanceInThread = NULL;

IOLoop::IOLoop() {
    if (_IOLoopInstanceInThread != NULL) {
        _instance = _IOLoopInstanceInThread;
    }
    else {
        _IOLoopInstanceInThread = this;
        _instance = this;
    }
}

void IOLoop::Loop() {
    auto p = [](auto a, auto b){return a+b;};
    while (!_quit) {

    }

}

IOLoop::~IOLoop() {
    _IOLoopInstanceInThread = NULL;
}
