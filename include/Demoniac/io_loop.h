//
// Created by Neveralso on 15/3/15.
//

#ifndef _DEMONIAC_IOLOOP_H_
#define _DEMONIAC_IOLOOP_H_

#include <iostream>
#include <vector>
#include <map>

#include "util/noncopyable.h"

namespace demoniac {


class Event;

namespace poller{

    class Poller;

    class KqueuePoller;

    class EpollPoller;

}


class IOLoop : demoniac::util::Noncopyable {
private:

    //IOLoop *instance_;
    bool quit_;
    demoniac::poller::Poller *poller_;
    std::map<int, Event> events_;

    IOLoop();

public:

    void AddEvent(const Event &e);

    static IOLoop *Current();

    void Loop();

    void Quit();

    void RemoveEvent(const int &fd);

    void Start();

    ~IOLoop();
};

}


#endif //_DEMONIAC_IOLOOP_H_
