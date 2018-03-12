#ifndef _ABATHUR_IOLOOP_HPP_
#define _ABATHUR_IOLOOP_HPP_

#include <iostream>
#include <vector>
#include <map>

namespace abathur {


    class EventCallback;

    namespace poller{

        class Poller;

        class KqueuePoller;

        class EpollPoller;

    }

    class Channel;

    class IOLoop {
    private:

        //IOLoop *instance_;
        bool quit_;
        abathur::poller::Poller *poller_;
        std::map<int, std::shared_ptr<Channel>> channel_map_;

        IOLoop();

        IOLoop(const IOLoop&) = delete;
        const IOLoop& operator=(const IOLoop&) = delete;

    public:

        static IOLoop* Current();

        void Loop();

        void Quit();

        void AddChannel(const int& fd, std::shared_ptr<Channel> channel);

        void RemoveChannel(const int &fd);

        void Start();

        ~IOLoop();
    };

}


#endif //_ABATHUR_IOLOOP_HPP_
