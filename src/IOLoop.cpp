//
// Created by Neveralso on 15/3/15.
//

#include "IOLoop.h"

#include <unistd.h>

#include "Log.h"

namespace dc {


__thread IOLoop
*
kIOLoopInstanceInThread = NULL;

IOLoop::IOLoop() {
    kIOLoopInstanceInThread = this;
    poller_ = GetPoller();
    events_.clear();
    quit_ = 0;
}


void IOLoop::AddEvent(const Event &e) {

#if defined(DC_DEBUG)
    LOG_DEBUG << "fd" << e.GetFD() << " Loop event added";
#endif

    events_.insert(std::make_pair(e.GetFD(), e));
    poller_->AddEvent(e);
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


void IOLoop::Loop() {
    LOG_INFO << "Loop start.";
    int ready_num;

#if defined(DC_DEBUG)
    int count = 0;
#endif

    while (!quit_) {

#if defined(DC_DEBUG)
        LOG_DEBUG << "Loop " << count++ << " with " << events_.size() <<" events";
#endif
        ready_num = poller_->Poll(10);

#if defined(DC_DEBUG)
        LOG_DEBUG << ready_num << " events ready";
#endif

        poller_->HandleEvents(ready_num, events_);

    }
}


void IOLoop::Quit() {
    quit_ = 1;

}


void IOLoop::RemoveEvent(const int &fd) {
#if defined(DC_DEBUG)
    LOG_DEBUG << "fd" << fd << " Loop event removed";
#endif
    events_.erase(fd);
}


void IOLoop::Start() {
    Loop();
}


IOLoop::~IOLoop() {
    kIOLoopInstanceInThread = NULL;
}


}