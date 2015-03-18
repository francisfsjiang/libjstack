//
// Created by Neveralso on 15/3/17.
//

#ifndef _DEMONIAC_POLLER_H_
#define _DEMONIAC_POLLER_H_

#include <vector>

#include "../util/noncopyable.h"
#include "../Event.h"



#if defined(__unix__) || defined(__MACH__)
    #include <sys/types.h>
    #include <sys/event.h>
    #include <sys/time.h>
#elif defined(__linux__)
    #include <sys/epoll.h>
#endif


namespace dc {


#if defined(__unix__) || defined(__MACH__)
typedef struct kevent poll_event;
#elif defined(__linux__)
typedef struct epoll_event poll_event;
#endif


class Poller : noncopyable {
private:
public:

    virtual int Poll(std::vector<poll_event>& events, int max_num_of_events) = 0;

    virtual void AddEvent(const Event &e) = 0;

    virtual void UpdateEvent(const Event &e) = 0;

    virtual void DeleteEvent(const Event &e) = 0;
};
}


#endif //_DEMONIAC_POLLER_H_
