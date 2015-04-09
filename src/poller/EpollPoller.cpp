//
// Created by Neveralso on 15/3/17.
//

#include "EpollPoller.h"

#include <cstring>
#include <linux/sockios.h>

#include "../Log.h"

namespace dc {

EpollPoller::EpollPoller() {
    events_ready_.resize(MAX_READY_EVENTS_NUM);
    epoll_ = epoll_create(MAX_READY_EVENTS_NUM);
    if (epoll_ < 0) {
        LOG_ERROR << "Epoll init failed " << strerror(errno);
        throw PollerError("Epoll init failed");
    }
#if defined(DC_DEBUG)
    LOG_DEBUG << "fd" << epoll_ << " Epoll created";
#endif
}

void EpollPoller::AddEvent(const Event &e) {
    poll_event event;
    int ret;
    event.events = 0;
    event.data.fd = e.GetFD();
    //Add read event
    if (e.has_read_callback()) {
        event.events |= EPOLLIN;
    }

    if (e.has_write_callback()) {
        event.events |= EPOLLOUT;
    }

    if (e.has_close_callback()) {
        event.events |= EPOLLRDHUP;
    }

    ret = epoll_ctl(epoll_, EPOLL_CTL_ADD, e.GetFD(), &event);
    if (ret < 0) {
        LOG_ERROR << "fd" << e.GetFD() << " Epoll event add failed " << strerror(errno);
        throw PollerError("Epoll event add failed");
    }

#if defined(DC_DEBUG)
    LOG_DEBUG << "fd" << e.GetFD() << " Epoll add event";
#endif
}

void EpollPoller::UpdateEvent(const Event &e) {
    poll_event event;
    int ret;
    event.events = 0;
    event.data.fd = e.GetFD();
    //Add read event
    if (e.has_read_callback()) {
        event.events |= EPOLLIN;
    }

    if (e.has_write_callback()) {
        event.events |= EPOLLOUT;
    }

    if (e.has_close_callback()) {
        event.events |= EPOLLRDHUP;
    }

    ret = epoll_ctl(epoll_, EPOLL_CTL_MOD, e.GetFD(), &event);
    if (ret < 0) {
        LOG_ERROR << "fd" << e.GetFD() << " Epoll event modify failed " << strerror(errno);
        throw PollerError("Epoll event modify failed");
    }

#if defined(DC_DEBUG)
    LOG_DEBUG << "fd" << e.GetFD() << " Epoll add event";
#endif
}

void EpollPoller::DeleteEvent(const Event &e) {
    int ret = epoll_ctl(epoll_, EPOLL_CTL_DEL, e.GetFD(), NULL);
    if (ret < 0) {
        LOG_ERROR << "fd" << e.GetFD() << " Epoll event delete failed" << strerror(errno);
        throw PollerError("Epoll event delete failed");
    }

    LOG_DEBUG << "fd" << e.GetFD() << " undefined delete event in epoll " << epoll_;
}

int EpollPoller::Poll(int time_out) {

    int ret = epoll_wait(epoll_, events_ready_.data(), MAX_READY_EVENTS_NUM, time_out*1000);
    if (ret < 0) {
        LOG_ERROR << "fd" << epoll_ << "epoll poll error occured. " << strerror(errno);
    }
    return ret;
}

void EpollPoller::HandleEvents(int ready_num, std::map<int, Event> &events) {
    int data_available;
    std::map<int, Event>::iterator iter;
    for (int i = 0; i < ready_num; ++i) {

#if defined(DC_DEBUG)
        poll_event e = events_ready_[i];
        LOG_DEBUG << "event num:" << i << " fd" << e.data.fd;
        LOG_DEBUG << "event num:" << i << " events" << e.events;
#endif
        iter = events.find(events_ready_[i].data.fd);
        if (iter == events.end()) {
            LOG_ERROR << events_ready_[i].data.fd << "event not found";
        }
        data_available = -1;
        ioctl(events_ready_[i].data.fd, FIONREAD, &data_available);
        if (iter->second.has_close_callback() &&
                (events_ready_[i].events & EPOLLRDHUP ||
                        events_ready_[i].events & EPOLLERR)) {
            iter->second.exec_close_callback(events_ready_[i].data.fd,
                    data_available);
        }
        if (iter->second.has_read_callback() &&
                (events_ready_[i].events & EPOLLIN)) {
            iter->second.exec_read_callback(events_ready_[i].data.fd,
                    data_available);
        }
        if (iter->second.has_close_callback() &&
                (events_ready_[i].events & EPOLLOUT)) {
            iter->second.exec_write_callback(events_ready_[i].data.fd,
                    data_available);
        }

    }
}
}

