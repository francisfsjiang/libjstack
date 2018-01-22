#include "abathur/io_loop.h"

#include "abathur/abathur.h"
#include "abathur/poller/get_poller.h"

namespace abathur {

__thread IOLoop
*
kIOLoopInstanceInThread = nullptr;

IOLoop::IOLoop() {
    kIOLoopInstanceInThread = this;
    poller_ = abathur::poller::GetPoller();
    events_map_.clear();
    quit_ = 0;
}


void IOLoop::AddEventCallback(const int& fd, EventCallback e) {

    LOG_DEBUG << "fd" << fd << " Loop event added";

    events_map_.insert(std::make_pair(fd, e));
    poller_->AddEventCallback(fd, e);
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

#if defined(ABATHUR_DEBUG)
    int count = 0;
#endif

    while (!quit_) {

#if defined(ABATHUR_DEBUG)
        LOG_DEBUG << "Loop " << count++ << " with " << events_map_.size() << " events";
#endif
        ready_num = poller_->Poll(10);

#if defined(ABATHUR_DEBUG)
        LOG_DEBUG << ready_num << " events ready";
#endif

        poller_->HandleEvents(ready_num, events_map_);

    }
}


void IOLoop::Quit() {
    quit_ = 1;

}


void IOLoop::RemoveEventCallback(const int &fd) {
#if defined(ABATHUR_DEBUG)
    LOG_DEBUG << "fd" << fd << " Loop event removed";
#endif
    events_map_.erase(fd);
}


void IOLoop::Start() {
    Loop();
}


IOLoop::~IOLoop() {
    delete poller_;
    kIOLoopInstanceInThread = NULL;
}


}