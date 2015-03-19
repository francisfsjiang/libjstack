//
// Created by Neveralso on 15/3/17.
//

#ifndef _DEMONIAC_KQUEUEPOLLER_H_
#define _DEMONIAC_KQUEUEPOLLER_H_

#include "Poller.h"

#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>

namespace dc {


class KqueuePoller : public Poller {
private:
    int kqueue_;

public:
    KqueuePoller();

    int Poll(std::vector<poll_event> &events,
            int max_num_of_events,
            int time_out);

    virtual void AddEvent(const Event &e);

    virtual void UpdateEvent(const Event &e);

    virtual void DeleteEvent(const Event &e);
};
}


#endif //_DEMONIAC_KQUEUEPOLLER_H_
