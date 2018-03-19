#include "abathur/io_loop.hpp"

#include "signal.h"

#include "abathur/abathur.hpp"
#include "abathur/channel.hpp"
#include "abathur/util/timer.hpp"
#include "abathur/poller/get_poller.hpp"

namespace abathur {

    thread_local IOLoop* kIOLoopInstanceInThread = nullptr;

    const int IOLoop::WAIT_TIME = 10;

    void signalHandler( int signum )
    {
        cout << "Interrupt signal (" << signum << ") received.\n";
        abathur::IOLoop::Current()->Quit();
        delete kIOLoopInstanceInThread;
    }


    bool Compare(util::Timer* a, util::Timer* b)
    {
        return a->get_time() < b->get_time();
    }

    IOLoop::IOLoop() {
        kIOLoopInstanceInThread = this;
        poller_ = abathur::poller::GetPoller();
        channel_map_.clear();
        quit_ = 0;
        timer_heap_ = timer_heap_type(
                [](util::Timer* a, util::Timer* b)->bool{
                    return a->get_time() < b->get_time();
                }
        );
        signal(SIGINT, signalHandler);
        signal(SIGABRT, signalHandler);

    }


    void IOLoop::AddChannel(int fd, uint filter, std::shared_ptr<Channel> channel) {

        LOG_TRACE << "Loop event adding, fd " << fd << " , filter " << filter;

        channel_map_.insert(std::make_pair(fd, std::make_pair(filter, channel)));
        poller_->AddChannel(fd, filter);
    }

    void IOLoop::SetChannelFilter(int fd, uint filter) {
        auto old_channel_iter = channel_map_.find(fd);
        uint old_filter = old_channel_iter->second.first;
        if (old_filter == filter) {
            LOG_DEBUG << "Setting, fd " << fd << " , from " << old_filter << " to " << filter << " , skipping.";
            return;
        }
        LOG_TRACE << "Loop event updating, fd " << fd << " , from " << old_filter << " to " << filter;
        poller_->UpdateChannel(fd, filter, old_filter);
        old_channel_iter->second = std::make_pair(filter, old_channel_iter->second.second);
    }

    void IOLoop::UpdateChannelFilter(int fd, uint filter) {
        LOG_TRACE << channel_map_[fd].second.use_count();
        auto old_channel_iter = channel_map_.find(fd);
        uint old_filter = old_channel_iter->second.first;
        if (old_filter & filter) {
            LOG_DEBUG << "Updating, fd " << fd << " , from " << old_filter << " , add " << filter << " , skipping.";
            return;
        }
        LOG_TRACE << "Loop event updating, fd " << fd << " , from " << old_filter << " add " << filter;
        poller_->UpdateChannel(fd, old_filter | filter, old_filter);
        old_channel_iter->second = std::make_pair(filter, old_channel_iter->second.second);
        LOG_TRACE << channel_map_[fd].second.use_count();
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
        int wait_time = WAIT_TIME;

        while (!quit_) {

            LOG_TRACE << "Loop " << count++ << " with " << channel_map_.size() << " wait_time " << wait_time
                      << " events ------------------------------------------------------";

            for(auto i: channel_map_) {
                LOG_TRACE << i.first << " " << i.second.second.use_count();
            }

            ready_num = poller_->Poll(wait_time);

            LOG_TRACE << ready_num << " events ready";

            if (ready_num > 0) {
                poller_->HandleEvents(ready_num, channel_map_);
            }

            wait_time = min(WAIT_TIME, process_timers());

            LOG_TRACE << "Doing channel removing.";
            while(channel_to_remove_pending_.size() > 0) {
                _remove_channel(channel_to_remove_pending_.front());
                channel_to_remove_pending_.pop();
            }
        }
    }


    void IOLoop::Quit() {
        quit_ = 1;
        channel_map_.clear();
    }


    void IOLoop::remove_channel(int fd) {
        channel_to_remove_pending_.push(fd);
    }

    void IOLoop::_remove_channel(int fd) {
        LOG_TRACE << "Loop removing channel on fd " << fd ;
        auto iter = channel_map_.find(fd);
        if (iter != channel_map_.end()){
            LOG_TRACE << "Loop event removing fd " << fd ;
            poller_->DeleteChannel(fd);
            channel_map_.erase(iter);
        }
    }


    void IOLoop::Start() {
        Loop();
    }


    IOLoop::~IOLoop() {
        delete poller_;
        kIOLoopInstanceInThread = NULL;
    }

    void IOLoop::add_timer(util::Timer* timer) {
        LOG_TRACE << "Adding timer, " << timer->get_time();
        timer_heap_.push(timer);
        timer_map_.insert(timer);
    }

    void IOLoop::delete_timer(util::Timer* timer) {
        LOG_TRACE << "Delete timer, " << timer->get_time();
        auto i = timer_map_.find(timer);
        if (i!=timer_map_.end()) {
            (*i)->cancel();
        }
    }

    int IOLoop::process_timers() {
        util::Timer* timer;
        int current_time = util::get_time();
        int wait_time = WAIT_TIME;
        LOG_TRACE << "Start processing timers, current: " << current_time << "-----";
        while (!timer_heap_.empty()) {
            LOG_TRACE << "Handling one timer.";
            timer = timer_heap_.top();
            timer_heap_.pop();
            //get current time
            current_time = util::get_time();
            if(timer->get_time() <= current_time) {
                if(!timer->canceled())
                    timer->process(current_time);

                if (timer->get_type() == util::ONCE || timer->canceled()) {
                    timer_map_.erase(timer);
                    delete timer;
                }
                else {
                    timer->set_time(current_time + timer->get_interval());
                    timer_heap_.push(timer);
                }

            }
            else {
                timer_heap_.push(timer);
                wait_time = timer->get_time() - util::get_time();
                break;
            }
        }
        if (wait_time < 0)
            wait_time = 0;
        return wait_time;
    }

}