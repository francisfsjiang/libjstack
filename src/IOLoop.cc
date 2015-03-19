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
        instance_ = this;
        poller_ = GetPoller();
        events_.clear();
        quit_ = 0;
        events_ready_.resize(MAX_EVENTS_READY_NUM);
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
        ready_num = poller_->Poll(events_ready_, MAX_EVENTS_READY_NUM, 5);

        //if (ready_num == 0) {

#if defined(DC_DEBUG)
            LOG_DEBUG << "sleeping";
#endif

            sleep(5);
        //}

#if defined(DC_DEBUG)
        LOG_DEBUG << ready_num << " events ready";
#endif

        for (int i = 0; i < ready_num; ++i) {

#if defined(DC_DEBUG)
            LOG_DEBUG << "fd " << events_ready_[i].ident;
            LOG_DEBUG << "data " << events_ready_[i].data;
#endif
            auto iter = events_.find(static_cast<int>(events_ready_[i].ident));
            if (iter != events_.end()) {
                iter->second.exec_read_call_back(
                        events_ready_[i].ident,
                        events_ready_[i].data);
            }
        }


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

void IOLoop::quit() {
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