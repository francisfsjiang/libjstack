//
// Created by Neveralso on 15/3/15.
//

#include <unistd.h>
#include "IOLoop.h"

#include "Log.h"

namespace dc {

__thread IOLoop
*
kIOLoopInstanceInThread = NULL;

IOLoop::IOLoop() {
    if (kIOLoopInstanceInThread != NULL) {
        LOG_CRITICAL << "Loop in this thread has existed";
    }
    else {
        kIOLoopInstanceInThread = this;
        //instance_ = this;
        poller_ = GetPoller();
        events_.clear();
        quit_ = 0;
    }
}

void IOLoop::Loop() {
    LOG_INFO << "Loop start.";
    int ready_num;
#if defined(DC_DEBUG)
    int count = 0;
#endif
    while (!quit_) {
#if defined(DC_DEBUG)
        LOG_DEBUG << "Looped " << count++;
#endif
        ready_num = poller_->Poll(10);

        //if (ready_num == 0) {

#if defined(DC_DEBUG)
        LOG_DEBUG << "sleeping";
#endif

        poller_->HandleEvents(ready_num, events_);

#if defined(DC_DEBUG)
        LOG_DEBUG << ready_num << " events ready";
#endif



    }
}

IOLoop::~IOLoop() {
    kIOLoopInstanceInThread = NULL;
}

void IOLoop::AddEvent(const Event &e) {
#if defined(DC_DEBUG)
    LOG_DEBUG << "Loop add fd= " << e.GetFD();
#endif
    events_.insert(std::make_pair(e.GetFD(), e));
    poller_->AddEvent(e);
}

void IOLoop::Quit() {
    quit_ = 1;

}

IOLoop *IOLoop::Current() {
    if (kIOLoopInstanceInThread) {
        return kIOLoopInstanceInThread;
    }
    else {
        kIOLoopInstanceInThread = new IOLoop;
        return kIOLoopInstanceInThread;
    }
}
}