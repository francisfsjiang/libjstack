//
// Created by Neveralso on 15/3/17.
//

#ifndef _DEMONIAC_KQUEUEPOLLER_H_
#define _DEMONIAC_KQUEUEPOLLER_H_

#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>

#include "Poller.h"

namespace dc {

class KqueuePoller : public Poller {
private:
    typedef struct kevent poll_event;

    int kqueue_;

    std::vector<poll_event> events_ready_;

public:
    KqueuePoller();

    virtual int Poll(int time_out);

    virtual void HandleEvents(int ready_num, std::map<int, Event> &events);

    virtual void AddEvent(const Event &e);

    virtual void UpdateEvent(const Event &e);

    virtual void DeleteEvent(const Event &e);
};
}


#endif //_DEMONIAC_KQUEUEPOLLER_H_
