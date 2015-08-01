//
// Created by Neveralso on 15/3/17.
//

#include "demoniac/poller/epoll_poller.h"

#include <cstring>
#include <linux/sockios.h>

#include "demoniac/log.h"
#include "demoniac/event.h"
#include "demoniac/util/error.h"

namespace demoniac {
namespace poller {

EpollPoller::EpollPoller() {
    events_ready_.resize(MAX_READY_EVENTS_NUM);
    epoll_ = epoll_create(MAX_READY_EVENTS_NUM);
    if (epoll_ < 0) {
        LOG_ERROR << "Epoll init failed " << strerror(errno);
        throw util::PollerError("Epoll init failed");
    }
#if defined(DC_DEBUG)
    LOG_DEBUG << "fd" << epoll_ << " Epoll created";
#endif
}

void EpollPoller::AddEvent(const int& fd, const EventCallback &e) {
    PollEvent poll_event;
    int ret;
    poll_event.events = 0;
    poll_event.data.fd = fd;
    //Add read event
    if (e.has_read_callback()) {
        poll_event.events |= EPOLLIN;
    }

    if (e.has_write_callback()) {
        poll_event.events |= EPOLLOUT;
    }

    if (e.has_close_callback()) {
        poll_event.events |= EPOLLRDHUP;
    }

    ret = epoll_ctl(epoll_, EPOLL_CTL_ADD, fd, &poll_event);
    if (ret < 0) {
        LOG_ERROR << "fd" << fd << " Epoll event add failed " << strerror(errno);
        throw util::PollerError("Epoll event add failed");
    }

    LOG_DEBUG << "fd" << fd << " Epoll add event";
}

void EpollPoller::UpdateEvent(const int& fd, const EventCallback &e) {
    poll_event event;
    int ret;
    event.events = 0;
    event.data.fd = fd;
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

    ret = epoll_ctl(epoll_, EPOLL_CTL_MOD, fd, &event);
    if (ret < 0) {
        LOG_ERROR << "fd" << fd << " Epoll event modify failed " << strerror(errno);
        throw util::PollerError("Epoll event modify failed");
    }

    LOG_DEBUG << "fd" << fd << " Epoll add event";
}

void EpollPoller::DeleteEvent(const int& fd, const EventCallback &e) {
    int ret = epoll_ctl(epoll_, EPOLL_CTL_DEL, fd, NULL);
    if (ret < 0) {
        LOG_ERROR << "fd" << fd << " Epoll event delete failed" << strerror(errno);
        throw util::PollerError("Epoll event delete failed");
    }

    LOG_DEBUG << "fd" << fd << " undefined delete event in epoll " << epoll_;
}

int EpollPoller::Poll(int time_out) {

    int ret = epoll_wait(epoll_, events_ready_.data(), MAX_READY_EVENTS_NUM, time_out * 1000);
    if (ret < 0) {
        LOG_ERROR << "fd" << epoll_ << "epoll poll error occured. " << strerror(errno);
    }
    return ret;
}

void EpollPoller::HandleEvents(const std::map<int, EventCallback>& events_map) {
    int data_available;
    std::map<int, Event>::iterator iter;
    for (int i = 0; i < ready_num; ++i) {

#if defined(DC_DEBUG)
        poll_event e = events_ready_[i];
        LOG_DEBUG << "event num:" << i << " fd" << e.data.fd;
        LOG_DEBUG << "event num:" << i << " events" << e.events;
#endif
        iter = events_map.find(events_ready_[i].data.fd);
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
}

