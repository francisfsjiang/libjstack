//
// Created by Neveralso on 15/3/17.
//

#ifndef _DEMONIAC_POLLER_KQUEUEPOLLER_H_
#define _DEMONIAC_POLLER_KQUEUEPOLLER_H_

#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>
#include <demoniac/event_callback.h>

#include "demoniac/poller/poller.h"

namespace demoniac {
namespace poller {


class KqueuePoller : public Poller {
private:
    typedef struct kevent PollEvent;

    int kqueue_fd_;

    std::vector<PollEvent> events_ready_;
    int events_ready_amount_;

public:
    KqueuePoller();

    virtual int Poll(int time_out);

    virtual void HandleEvents(const std::map<int, EventCallback>& events_map);

    virtual void AddEventCallback(const int& fd, const EventCallback& e);

    virtual void UpdateEventCallback(const int& fd, const EventCallback& e);

    virtual void DeleteEventCallback(const int& fd);
};


}
}


#endif //_DEMONIAC_KQUEUEPOLLER_H_
