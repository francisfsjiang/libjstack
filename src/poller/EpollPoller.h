//
// Created by Neveralso on 15/3/17.
//

#ifndef _DEMONIAC_EPOLLPOLLER_H_
#define _DEMONIAC_EPOLLPOLLER_H_

#include "Poller.h"

#include <sys/epoll.h>
#include <sys/ioctl.h>

#include "../Event.h"

namespace dc {

class EpollPoller : public Poller {
private:
    typedef struct epoll_event poll_event;

    int epoll_;

    std::vector<poll_event> events_ready_;

public:
    EpollPoller();

    virtual int Poll(int time_out);

    virtual void HandleEvents(int ready_num, std::map<int, Event> &events);

    virtual void AddEvent(const Event &e);

    virtual void UpdateEvent(const Event &e);

    virtual void DeleteEvent(const Event &e);
};

}


#endif //_DEMONIAC_EPOLLPOLLER_H_
