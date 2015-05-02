//
// Created by Neveralso on 15/3/17.
//

#ifndef _DEMONIAC_POLLER_POLLER_H_
#define _DEMONIAC_POLLER_POLLER_H_

#include <vector>
#include <map>

#include "demoniac/util/noncopyable.h"

namespace demoniac {

class Event;

namespace poller {

const int MAX_READY_EVENTS_NUM = 500;

class Poller : demoniac::util::Noncopyable {
private:
public:

    virtual int Poll(int time_out) = 0;

    virtual void HandleEvents(int ready_num, std::map<int, Event> &events) = 0;

    virtual void AddEvent(const demoniac::Event &e) = 0;

    virtual void UpdateEvent(const Event &e) = 0;

    virtual void DeleteEvent(const Event &e) = 0;
};


}
}


#endif //_DEMONIAC_POLLER_H_
