#include "abathur/poller/epoll_poller.h"

#include <cstring>
#include <linux/sockios.h>

#include "abathur/log.h"
#include "abathur/event_callback.h"
#include "abathur/util/error.h"

namespace abathur::poller {

    EpollPoller::EpollPoller() {
        events_ready_.resize(MAX_READY_EVENTS_NUM);
        epoll_fd_ = epoll_create(MAX_READY_EVENTS_NUM);
        if (epoll_fd_ < 0) {
            LOG_ERROR << "Epoll init failed " << strerror(errno);
            throw util::PollerError("Epoll init failed");
        }
#if defined(ABATHUR_DEBUG)
        LOG_DEBUG << "fd" << epoll_fd_ << " Epoll created.";
#endif
    }

EpollPoller::~EpollPoller() {
#if defined(ABATHUR_DEBUG)
        LOG_DEBUG << "fd" << epoll_fd_ << " Epoll destoried.";
#endif
    }
    
    void EpollPoller::AddEventCallback(const int &fd, const EventCallback &e) {
        PollEvent epoll_event;
        int ret;
        epoll_event.events = 0;
        epoll_event.data.fd = fd;
        //Add read event
        if (e.HasReadCallback()) {
            epoll_event.events |= EPOLLIN;
        }

        if (e.HasWriteCallback()) {
            epoll_event.events |= EPOLLOUT;
        }

        if (e.HasCloseCallback()) {
            epoll_event.events |= EPOLLRDHUP;
        }

        ret = epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, fd, &epoll_event);
        if (ret < 0) {
            LOG_ERROR << "fd" << fd << " Epoll event add failed " << strerror(errno);
            throw util::PollerError("Epoll event add failed");
        }

        LOG_DEBUG << "fd" << fd << " Epoll add event";
    }

    void EpollPoller::UpdateEventCallback(const int &fd, const EventCallback &e) {
        epoll_event event;
        int ret;
        event.events = 0;
        event.data.fd = fd;
        //Add read event
        if (e.HasReadCallback()) {
            event.events |= EPOLLIN;
        }

        if (e.HasWriteCallback()) {
            event.events |= EPOLLOUT;
        }

        if (e.HasCloseCallback()) {
            event.events |= EPOLLRDHUP;
        }

        ret = epoll_ctl(epoll_fd_, EPOLL_CTL_MOD, fd, &event);
        if (ret < 0) {
            LOG_ERROR << "fd" << fd << " Epoll event modify failed " << strerror(errno);
            throw util::PollerError("Epoll event modify failed");
        }

        LOG_DEBUG << "fd" << fd << " Epoll add event";
    }

    void EpollPoller::DeleteEventCallback(const int &fd) {
        int ret = epoll_ctl(epoll_fd_, EPOLL_CTL_DEL, fd, NULL);
        if (ret < 0) {
            LOG_ERROR << "fd" << fd << " Epoll event delete failed" << strerror(errno);
            throw util::PollerError("Epoll event delete failed");
        }

        LOG_DEBUG << "fd" << fd << " undefined delete event in epoll " << epoll_fd_;
    }

    int EpollPoller::Poll(int time_out) {

        int ret = epoll_wait(epoll_fd_, events_ready_.data(), MAX_READY_EVENTS_NUM, time_out * 1000);
        if (ret < 0) {
            LOG_ERROR << "fd" << epoll_fd_ << "epoll poll error occured. " << strerror(errno);
        }
        return ret;
    }

    void EpollPoller::HandleEvents(const int& events_ready_amount, const std::map<int, EventCallback>& events_map) {
        int data_available;
        for (int i = 0; i < events_ready_amount; ++i) {

#if defined(ABATHUR_DEBUG)
            epoll_event e = events_ready_[i];
        LOG_DEBUG << "event num:" << i << " fd" << e.data.fd;
        LOG_DEBUG << "event num:" << i << " events" << e.events;
#endif
            auto iter = events_map.find(events_ready_[i].data.fd);
            if (iter == events_map.end()) {
                LOG_ERROR << events_ready_[i].data.fd << "event not found";
            }
            data_available = -1;
            ioctl(events_ready_[i].data.fd, FIONREAD, &data_available);
            if (iter->second.HasCloseCallback() &&
                (events_ready_[i].events & EPOLLRDHUP ||
                 events_ready_[i].events & EPOLLERR)) {
                iter->second.ExecCloseCallback(events_ready_[i].data.fd,
                                                 data_available);
            }
            if (iter->second.HasReadCallback() &&
                (events_ready_[i].events & EPOLLIN)) {
                iter->second.ExecReadCallback(events_ready_[i].data.fd,
                                                data_available);
            }
            if (iter->second.HasCloseCallback() &&
                (events_ready_[i].events & EPOLLOUT)) {
                iter->second.ExecWriteCallback(events_ready_[i].data.fd,
                                                 data_available);
            }

        }
    }


}

