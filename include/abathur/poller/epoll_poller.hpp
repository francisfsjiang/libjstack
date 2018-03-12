#ifndef _ABATHUR_POLLER_EPOLLPOLLER_HPP_
#define _ABATHUR_POLLER_EPOLLPOLLER_HPP_

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

        ~EpollPoller() override ;

        int Poll(int time_out) override ;

        virtual void HandleEvents(
                const int& events_ready_amount,
                const std::map<int, std::shared_ptr<Channel>>& channel_map) override ;

        virtual void AddChannel(int fd, std::shared_ptr<Channel>) override ;

//        virtual void UpdateChannel(const int& fd, const Channel& e) override ;

        virtual void DeleteChannel(const int& fd) override ;
    };

}


#endif //_ABATHUR_EPOLLPOLLER_HPP_
