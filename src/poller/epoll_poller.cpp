#include "abathur/poller/epoll_poller.hpp"

#include <cstring>
#include <linux/sockios.h>

#include "abathur/log.hpp"
#include "abathur/error.hpp"
#include "abathur/channel.hpp"
#include "abathur/event.hpp"

namespace abathur::poller {

    EpollPoller::EpollPoller() {
        events_ready_.resize(MAX_READY_EVENTS_NUM);
        epoll_fd_ = epoll_create(MAX_READY_EVENTS_NUM);
        if (epoll_fd_ < 0) {
            LOG_ERROR << "Epoll init failed " << strerror(errno);
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
    
    void EpollPoller::AddChannel(int fd) {
        PollEvent epoll_event;
        int ret;
        epoll_event.events = 0;
        epoll_event.data.fd = fd;
        //Add read event
        epoll_event.events |= EPOLLIN;
        epoll_event.events |= EPOLLOUT;
        epoll_event.events |= EPOLLRDHUP;

        ret = epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, fd, &epoll_event);
        if (ret < 0) {
            LOG_ERROR << "fd" << fd << " Epoll event add failed " << strerror(errno);
        }

        LOG_DEBUG << "fd" << fd << " Epoll add event";
    }

//    void EpollPoller::UpdateChannel(const int &fd, const Channel &e) {
//        epoll_event event;
//        int ret;
//        event.events = 0;
//        event.data.fd = fd;
//        //Add read event
//        if (e.HasReadCallback()) {
//            event.events |= EPOLLIN;
//        }
//
//        if (e.HasWriteCallback()) {
//            event.events |= EPOLLOUT;
//        }
//
//        if (e.HasCloseCallback()) {
//            event.events |= EPOLLRDHUP;
//        }
//
//        ret = epoll_ctl(epoll_fd_, EPOLL_CTL_MOD, fd, &event);
//        if (ret < 0) {
//            LOG_ERROR << "fd" << fd << " Epoll event modify failed " << strerror(errno);
//        }
//
//        LOG_DEBUG << "fd" << fd << " Epoll add event";
//    }

    void EpollPoller::DeleteChannel(int fd) {
        int ret = epoll_ctl(epoll_fd_, EPOLL_CTL_DEL, fd, NULL);
        if (ret < 0) {
            LOG_ERROR << "fd" << fd << " Epoll event delete failed" << strerror(errno);
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

    void EpollPoller::HandleEvents(
            const int& events_ready_amount,
            const std::map<int, std::shared_ptr<Channel>>& channel_map
    ) {
        int data_available;
        for (int i = 0; i < events_ready_amount; ++i) {

#if defined(ABATHUR_DEBUG)
            epoll_event event = events_ready_[i];
        LOG_DEBUG << "event num:" << i << " fd" << event.data.fd;
        LOG_DEBUG << "event num:" << i << " events" << event.events;
#endif
            auto iter = channel_map.find(event.data.fd);
            if (iter == channel_map.end()) {
                LOG_ERROR << event.data.fd << "event not found";
            }
            data_available = -1;
            ioctl(event.data.fd, FIONREAD, &data_available);
            iter->second->Process(Event(
                        event.data.fd,
                        events_ready_[i].events & EPOLLIN,
                        events_ready_[i].events & EPOLLOUT,
                        events_ready_[i].events & EPOLLRDHUP || events_ready_[i].events & EPOLLERR
                        ));

        }
    }


}

