#include "abathur/io_loop.hpp"

#include "abathur/abathur.hpp"
#include "abathur/channel.hpp"
#include "abathur/poller/get_poller.hpp"

namespace abathur {

__thread IOLoop
*
kIOLoopInstanceInThread = nullptr;

IOLoop::IOLoop() {
    kIOLoopInstanceInThread = this;
    poller_ = abathur::poller::GetPoller();
    channel_map_.clear();
    quit_ = 0;
}


void IOLoop::AddChannel(const int& fd, std::shared_ptr<Channel> channel) {

    LOG_DEBUG << "fd" << fd << " Loop event added";

    channel_map_.insert(std::make_pair(fd, channel));
    poller_->AddChannel(fd);
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
        LOG_DEBUG << "Loop " << count++ << " with " << channel_map_.size() << " events";
#endif
        ready_num = poller_->Poll(10);

#if defined(ABATHUR_DEBUG)
        LOG_DEBUG << ready_num << " events ready";
#endif

        poller_->HandleEvents(ready_num, channel_map_);

    }
}


void IOLoop::Quit() {
    quit_ = 1;

}


void IOLoop::RemoveChannel(const int &fd) {
#if defined(ABATHUR_DEBUG)
    LOG_DEBUG << "fd" << fd << " Loop event removed";
#endif
    channel_map_.erase(fd);
}


void IOLoop::Start() {
    Loop();
}


IOLoop::~IOLoop() {
    delete poller_;
    kIOLoopInstanceInThread = NULL;
}


}