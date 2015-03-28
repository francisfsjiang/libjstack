//
// Created by Neveralso on 15/3/15.
//

#ifndef _DEMONIAC_IOLOOP_H_
#define _DEMONIAC_IOLOOP_H_

#include <iostream>
#include <vector>
#include <map>

#include "Event.h"
#include "util/noncopyable.h"

#include "poller/GetPoller.h"

namespace dc {

class IOLoop : noncopyable {
private:

    //IOLoop *instance_;
    bool quit_;
    Poller *poller_;
    std::map<int, Event> events_;

    IOLoop();

public:
    
    static IOLoop *Current();

    void Loop();

    void AddEvent(const Event &e);

    void RemoveEvent(const int &fd);

    void Quit();

    ~IOLoop();
};

}


#endif //_DEMONIAC_IOLOOP_H_
