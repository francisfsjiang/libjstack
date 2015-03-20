//
// Created by Neveralso on 15/3/17.
//

#include "KqueuePoller.h"

#include "../Log.h"

namespace dc {

KqueuePoller::KqueuePoller() {
    kqueue_ = kqueue();
    if (kqueue_ < 0) {
        LOG_CRITICAL << "kqueue init failed.";
    }
#if defined(DC_DEBUG)
    LOG_DEBUG << "Kqueue created fd=" << kqueue_;
#endif
}

void KqueuePoller::AddEvent(const Event &e) {
    poll_event event;
    EV_SET(&event, e.GetFD(), EVFILT_READ, EV_ADD, 0, 0, NULL);
    int ret = kevent(kqueue_, &event, 1, NULL, 0, NULL);
    if (ret < 0) {
        LOG_CRITICAL << "event add failed. fd= " << e.GetFD();
    }
#if defined(DC_DEBUG)
    LOG_DEBUG << "Kqueue add fd=" << e.GetFD();
#endif
}

void KqueuePoller::UpdateEvent(const Event &e) {
    LOG_DEBUG << e.GetFD() << " event add to " << kqueue_;
}

void KqueuePoller::DeleteEvent(const Event &e) {
    LOG_DEBUG << e.GetFD() << " event add to " << kqueue_;
}

int KqueuePoller::Poll(std::vector<poll_event> &events,
        int max_num_of_events,
        int time_out) {
#if defined(DC_DEBUG)
    LOG_DEBUG << "Poll timeout " << time_out;
#endif
    struct timespec time_sec = {time_out, 0};
    int ret = kevent(kqueue_, NULL, 0, events.data(), max_num_of_events, &time_sec);
    return ret;
}


}