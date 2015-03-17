//
// Created by Neveralso on 15/3/17.
//

#ifndef _DEMONIAC_POLLER_H_
#define _DEMONIAC_POLLER_H_

#include "../util/noncopyable.h"
#include "../Event.h"

namespace dc {

class Poller : noncopyable {
private:
public:

    virtual void Poll() = 0;

    virtual void AddEvent(const Event &e) = 0;

    virtual void UpdateEvent(const Event &e) = 0;

    virtual void DeleteEvent(const Event &e) = 0;
};
}


#endif //_DEMONIAC_POLLER_H_
