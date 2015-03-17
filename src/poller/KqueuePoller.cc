//
// Created by Neveralso on 15/3/17.
//

#include "KqueuePoller.h"

#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>

#include "../Log.h"

namespace dc {


KqueuePoller::KqueuePoller() {
    kqueue_ = kqueue();
}

void KqueuePoller::AddEvent(const Event &e) {
    struct kevent event;
    EV_SET(&event, e.GetFD(), EVFILT_READ, EV_ADD, 0, 0, NULL);
    int ret = kevent(kqueue_, &event, 1, NULL, 0, NULL);
    if (ret < 0) {
        LOG_CRITICAL<<"kqueue init failed.";
    }
}

void KqueuePoller::UpdateEvent(const Event &e) {
    LOG_DEBUG<<e.GetFD()<<" event add to "<<kqueue_;
}

void KqueuePoller::DeleteEvent(const Event &e) {
    LOG_DEBUG<<e.GetFD()<<" event add to "<<kqueue_;
}

void KqueuePoller::Poll() {

}
}