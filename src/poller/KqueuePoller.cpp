//
// Created by Neveralso on 15/3/17.
//

#include "KqueuePoller.h"

#include <unistd.h>

#include "../Log.h"

namespace dc {

KqueuePoller::KqueuePoller() {
    kqueue_ = kqueue();
    if (kqueue_ < 0) {
        LOG_ERROR << "kqueue init failed.";
    }
#if defined(DC_DEBUG)
    LOG_DEBUG << "Kqueue created fd=" << kqueue_;
#endif
}

void KqueuePoller::AddEvent(const Event &e) {
    poll_event event;
    int ret;
    //Add read event
    if (e.has_read_callback()) {
        EV_SET(&event, e.GetFD(), EVFILT_READ, EV_ADD, 0, 0, NULL);
        ret = kevent(kqueue_, &event, 1, NULL, 0, NULL);
        if (ret < 0) {
            LOG_ERROR << e.GetFD() << "event read add failed." << strerror(errno);
        }
    }

    if (e.has_write_callback()) {
        //Add write event
        EV_SET(&event, e.GetFD(), EVFILT_WRITE, EV_ADD, 0, 0, NULL);
        ret = kevent(kqueue_, &event, 1, NULL, 0, NULL);
        if (ret < 0) {
            LOG_ERROR << e.GetFD() << "event write add failed." << strerror(errno);
        }
    }

#if defined(DC_DEBUG)
    LOG_DEBUG << e.GetFD() << "Kqueue add fd=";
#endif
}

void KqueuePoller::UpdateEvent(const Event &e) {
    LOG_DEBUG << e.GetFD() << " undefined update event int kqueue " << kqueue_;
}

void KqueuePoller::DeleteEvent(const Event &e) {
    close(e.GetFD());
    LOG_DEBUG << e.GetFD() << " undefined delete event int kqueue " << kqueue_;
}

int KqueuePoller::Poll(int time_out) {
#if defined(DC_DEBUG)
    LOG_DEBUG << "Poll timeout " << time_out;
#endif
    struct timespec time_sec = {time_out, 0};
    int ret = kevent(kqueue_, NULL, 0, events_ready_.data(), MAX_READY_EVENTS_NUM, &time_sec);
    if (ret < 0) {
        LOG_ERROR << "kevent poll error occured. " << strerror(errno);
    }
    return ret;
}

void KqueuePoller::HandleEvents(int ready_num, std::map<int, Event> &events) {
    for (int i = 0; i < ready_num; ++i) {

#if defined(DC_DEBUG)
        LOG_DEBUG << "fd " << events_ready_[i].ident;
        LOG_DEBUG << "data " << events_ready_[i].data;
#endif
        auto iter = events.find(static_cast<int>(events_ready_[i].ident));
        if (iter != events.end()) {
            iter->second.exec_read_callback(
                    events_ready_[i].ident,
                    events_ready_[i].data);
        }
    }
}
}