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
                util::Timer*,
                std::vector<util::Timer*>,
                std::function<bool(util::Timer*, util::Timer*)>
        > timer_heap_type;
        timer_heap_type timer_heap_;
        std::set<util::Timer*> timer_map_;

        IOLoop();

        IOLoop(const IOLoop&) = delete;
        const IOLoop& operator=(const IOLoop&) = delete;

        void Loop();

        void _remove_channel(int);
        std::queue<int> channel_to_remove_pending_;
    public:

        static IOLoop* Current();

        void Quit();

        void AddChannel(int, uint, std::shared_ptr<Channel>);
        void UpdateChannelFilter(int, uint);
        void SetChannelFilter(int, uint);
        void remove_channel(int);

        int process_timers();
        void add_timer(util::Timer*);
        void delete_timer(util::Timer*);

        void Start();

        ~IOLoop();
    };

}


#endif //_ABATHUR_IOLOOP_HPP_
