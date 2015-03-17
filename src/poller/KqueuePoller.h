//
// Created by Neveralso on 15/3/17.
//

#ifndef _DEMONIAC_KQUEUEPOLLER_H_
#define _DEMONIAC_KQUEUEPOLLER_H_

#include "Poller.h"

namespace dc {
class KqueuePoller : Poller {
private:
    int _kqueue;
public:
    KqueuePoller();

    virtual void AddEvent(const Event &e);

    virtual void UpdateEvent(const Event &e);

    virtual void DeleteEvent(const Event &e);
};
}


#endif //_DEMONIAC_KQUEUEPOLLER_H_
