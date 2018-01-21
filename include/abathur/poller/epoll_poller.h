#ifndef _ABATHUR_POLLER_EPOLLPOLLER_H_
#define _ABATHUR_POLLER_EPOLLPOLLER_H_

#include <sys/epoll.h>
#include <sys/ioctl.h>

#include "abathur/poller/poller.h"

namespace abathur {
namespace poller {


class EpollPoller : public Poller {
private:
    typedef struct epoll_event PollEvent;

    int epoll_fd_;

    std::vector<PollEvent> events_ready_;
    int events_ready_amount_;

public:
    EpollPoller();

    int Poll(int time_out);

    virtual void HandleEvents(const std::map<int, EventCallback>& events_map);

    virtual void AddEventCallback(const int& fd, const EventCallback& e);

    virtual void UpdateEventCallback(const int& fd, const EventCallback& e);

    virtual void DeleteEventCallback(const int& fd);
};

}
}


#endif //_ABATHUR_EPOLLPOLLER_H_
