//
// Created by Neveralso on 15/3/15.
//

#ifndef _DEMONIAC_IOLOOP_H_
#define _DEMONIAC_IOLOOP_H_

#include <iostream>

#include "Event.h"
#include "util/noncopyable.h"
#include "poller/Poller.h"
#include "poller/KqueuePoller.h"
#include "poller/EpollPoller.h"

namespace dc {

class IOLoop : noncopyable {
private:
    IOLoop *instance_;
    bool quit_;
    Poller *poller_ = new KqueuePoller();
public:
    IOLoop();

    void Loop();

    void AddEvent(const Event& e);

    void RemoveEvent(const Event& e);

    ~IOLoop();
};

}


#endif //_DEMONIAC_IOLOOP_H_
