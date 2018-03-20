#ifndef _ABATHUR_POLLER_EPOLLPOLLER_HPP_
#define _ABATHUR_POLLER_EPOLLPOLLER_HPP_

#include <memory>

#include <sys/epoll.h>
#include <sys/ioctl.h>

#include "abathur/poller/poller.hpp"

namespace abathur::poller {


    typedef struct epoll_event PollEvent;

    class EpollPoller : public Poller {
    private:

        int epoll_fd_;

        std::vector<PollEvent> events_ready_;

    public:
        EpollPoller();

        virtual ~EpollPoller() override ;

        virtual int poll(int) override ;

        virtual void handle_events(
                const int& events_ready_amount,
                const std::map<int, std::pair<uint, std::shared_ptr<Channel>>>& channel_map
        ) override ;

        virtual void add_channel(int, uint) override ;

        virtual void update_channel(int, uint, uint) override ;

        virtual void delete_channel(int) override ;
    };

}


#endif //_ABATHUR_EPOLLPOLLER_HPP_
