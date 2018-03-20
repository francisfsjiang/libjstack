#ifndef _ABATHUR_IOLOOP_HPP_
#define _ABATHUR_IOLOOP_HPP_

#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <queue>
#include <set>
#include <functional>

namespace abathur {

    namespace util {
        class Timer;
    }

    namespace poller{
        class Poller;
        class KqueuePoller;
        class EpollPoller;
    }

    class Channel;

    class IOLoop {
    private:
        static const int WAIT_TIME;

        //IOLoop *instance_;
        bool quit_;
        abathur::poller::Poller *poller_;
        std::map<int, std::pair<uint, std::shared_ptr<Channel>>> channel_map_;

        typedef std::priority_queue<
                std::shared_ptr<util::Timer>,
                std::vector<std::shared_ptr<util::Timer>>,
                std::function<bool(std::shared_ptr<util::Timer>, std::shared_ptr<util::Timer>)>
        > timer_heap_type;
        timer_heap_type timer_heap_;
        std::set<std::shared_ptr<util::Timer>> timer_map_;

        IOLoop();

        IOLoop(const IOLoop&) = delete;
        const IOLoop& operator=(const IOLoop&) = delete;

        void Loop();

        void _remove_channel(int);
        std::queue<int> channel_to_remove_pending_;
    public:

        static IOLoop* current();

        void quit();

        void add_channel(int, uint, std::shared_ptr<Channel>);
        void update_channel_filter(int, uint);
        void set_channel_filter(int, uint);
        void remove_channel(int);

        int process_timers();
        void add_timer(std::shared_ptr<util::Timer>);
        void delete_timer(std::shared_ptr<util::Timer>);

        void start();

        ~IOLoop();
    };

}


#endif //_ABATHUR_IOLOOP_HPP_
