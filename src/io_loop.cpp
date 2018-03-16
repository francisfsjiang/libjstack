#include "abathur/io_loop.hpp"

#include "signal.h"

#include "abathur/abathur.hpp"
#include "abathur/channel.hpp"
#include "abathur/poller/get_poller.hpp"

namespace abathur {


    void signalHandler( int signum )
    {
        cout << "Interrupt signal (" << signum << ") received.\n";
        abathur::IOLoop::Current()->Quit();
    }

//__thread IOLoop
//*
//kIOLoopInstanceInThread = nullptr;
    thread_local IOLoop* kIOLoopInstanceInThread = nullptr;

    IOLoop::IOLoop() {
        kIOLoopInstanceInThread = this;
        poller_ = abathur::poller::GetPoller();
        channel_map_.clear();
        quit_ = 0;

        signal(SIGINT, signalHandler);
        signal(SIGABRT, signalHandler);

    }


    void IOLoop::AddChannel(int fd, uint filter, std::shared_ptr<Channel> channel) {

        LOG_DEBUG << "Loop event adding, fd " << fd << " , filter " << filter;

        channel_map_.insert(std::make_pair(fd, std::make_pair(filter, channel)));
        poller_->AddChannel(fd, filter);
    }

    void IOLoop::UpdateChannel(int fd, uint filter) {

        auto old = channel_map_.find(fd)->second;
        LOG_DEBUG << "Loop event updating, fd " << fd << " , from " << old.first << " to " << filter;
        poller_->UpdateChannel(fd, filter, old.first);
        channel_map_[fd] = std::make_pair(filter, old.second);
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

        int count = 0;

        while (!quit_) {

            LOG_TRACE << "Loop " << count++ << " with " << channel_map_.size() << " events";

            ready_num = poller_->Poll(10);

            LOG_TRACE << ready_num << " events ready";

            poller_->HandleEvents(ready_num, channel_map_);

        }
    }


    void IOLoop::Quit() {
        quit_ = 1;
        channel_map_.clear();
    }


    void IOLoop::RemoveChannel(int fd) {
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