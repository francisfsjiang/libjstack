//
// Created by Neveralso on 15/3/15.
//

#ifndef _DEMONIAC_IOLOOP_H_
#define _DEMONIAC_IOLOOP_H_

#include <iostream>
#include <vector>
#include <map>

#include "demoniac/util/noncopyable.h"

namespace demoniac {


class EventCallback;

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
    std::map<int, EventCallback> events_map_;

    IOLoop();

public:

    static IOLoop* Current();

    void Loop();

    void Quit();

    void AddEventCallback(const int& fd, EventCallback e);

    void RemoveEventCallback(const int &fd);

    void Start();

    ~IOLoop();
};

}


#endif //_DEMONIAC_IOLOOP_H_
