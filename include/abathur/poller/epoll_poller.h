#ifndef _ABATHUR_POLLER_EPOLLPOLLER_H_
#define _ABATHUR_POLLER_EPOLLPOLLER_H_

#include <sys/epoll.h>
#include <sys/ioctl.h>

#include "abathur/poller/poller.h"

namespace abathur::poller {


    class EpollPoller : public Poller {
    private:
        typedef struct epoll_event PollEvent;

        int epoll_fd_;

        std::vector<PollEvent> events_ready_;

    public:
        EpollPoller();

        ~EpollPoller() override ;

        int Poll(int time_out) override ;

        virtual void HandleEvents(const int& events_ready_amount, eventconst std::map<int, EventCallback>& events_map) override ;

        virtual void AddEventCallback(const int& fd, const EventCallback& e) override ;

        virtual void UpdateEventCallback(const int& fd, const EventCallback& e) override ;

        virtual void DeleteEventCallback(const int& fd) override ;
    };

}


#endif //_ABATHUR_EPOLLPOLLER_H_
