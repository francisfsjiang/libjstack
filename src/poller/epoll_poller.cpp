#include "abathur/poller/epoll_poller.hpp"

#include <cstring>

#include <linux/sockios.h>
#include <sys/epoll.h>

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
        LOG_DEBUG << "fd" << epoll_fd_ << " Epoll created.";
    }

EpollPoller::~EpollPoller() {
        LOG_DEBUG << "fd" << epoll_fd_ << " Epoll destoried.";
    }
    
    void EpollPoller::AddChannel(int fd, uint filter) {
        PollEvent poll_event;
        poll_event.events = 0;
        poll_event.data.fd = fd;

        if (filter & EF_READ){
            poll_event.events |= EPOLLIN;
        }

        if (filter & EF_WRITE) {
            poll_event.events |= EPOLLOUT;
        }

        if (filter & EF_CLOSE) {
            poll_event.events |= EPOLLRDHUP;
        }

        int ret = epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, fd, &poll_event);
        if (ret < 0) {
            LOG_ERROR << "fd" << fd << " Epoll event add failed " << strerror(errno);
        }

        LOG_DEBUG << "fd" << fd << " Epoll add event";
    }

    void EpollPoller::UpdateChannel(int fd, uint filter, uint) {
        PollEvent poll_event;
        poll_event.events = 0;
        poll_event.data.fd = fd;
        if (filter & EF_READ){
            poll_event.events |= EPOLLIN;
        }

        if (filter & EF_WRITE) {
            poll_event.events |= EPOLLOUT;
        }

        if (filter & EF_CLOSE) {
            poll_event.events |= EPOLLRDHUP;
        }

        int ret = epoll_ctl(epoll_fd_, EPOLL_CTL_MOD, fd, &poll_event);
        if (ret < 0) {
            LOG_ERROR << "fd" << fd << " Epoll event modify failed " << strerror(errno);
        }

        LOG_DEBUG << "fd" << fd << " Epoll add event";
    }

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
            const std::map<int, std::pair<uint, std::shared_ptr<Channel>>>& channel_map
    ) {
        for (int i = 0; i < events_ready_amount; ++i) {

            epoll_event event = events_ready_[i];

            LOG_DEBUG << "event num:" << i << " fd" << event.data.fd;
            LOG_DEBUG << "event num:" << i << " events" << event.events;

            auto iter = channel_map.find(event.data.fd);
            if (iter == channel_map.end()) {
                LOG_ERROR << event.data.fd << "event not found";
            }

            int filter = 0;
            filter |= events_ready_[i].events & EPOLLIN ? EF_READ: 0;
            filter |= events_ready_[i].events & EPOLLOUT ? EF_WRITE: 0;
            filter |= events_ready_[i].events & EPOLLRDHUP || events_ready_[i].events & EPOLLERR ? EF_CLOSE: 0;

            auto info_pair = iter->second;
            info_pair.second->Process(Event(
                        event.data.fd,
                        filter
                        ));

        }
    }


}

