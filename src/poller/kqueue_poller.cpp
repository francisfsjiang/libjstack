#include "abathur/poller/kqueue_poller.hpp"

#include <unistd.h>

#include "abathur/abathur.hpp"

#include "abathur/channel.hpp"
#include "abathur/event.hpp"

namespace abathur::poller {

    KqueuePoller::KqueuePoller() {
        events_ready_.resize(MAX_READY_EVENTS_NUM);
        kqueue_fd_ = kqueue();
        if (kqueue_fd_ < 0) {
            LOG_ERROR << "Kqueue init failed.";
        }
#if defined(ABATHUR_DEBUG)
        LOG_TRACE << "fd" << kqueue_fd_ << " Kqueue created.";
#endif
    }

    KqueuePoller::~KqueuePoller() {
#if defined(ABATHUR_DEBUG)
        LOG_TRACE << "fd" << kqueue_fd_ << " Kqueue destoried.";
#endif
    }

    void KqueuePoller::AddChannel(int fd, uint filter) {
        PollEvent poll_event;
        if (filter & EF_READ){
            EV_SET(&poll_event, fd, EVFILT_READ, EV_ADD, 0, 0, NULL);
            int ret = kevent(kqueue_fd_, &poll_event, 1, NULL, 0, NULL);
            if (ret < 0) {
                LOG_ERROR << fd << "Channel add failed" << strerror(errno);
            }
        }

        if (filter & EF_WRITE) {
            EV_SET(&poll_event, fd, EVFILT_WRITE, EV_ADD, 0, 0, NULL);
            int ret = kevent(kqueue_fd_, &poll_event, 1, NULL, 0, NULL);
            if (ret < 0) {
                LOG_ERROR << fd << "Channel add failed" << strerror(errno);
            }
        }

        LOG_TRACE << "Kqueue add event fd " << fd ;
    }

    void KqueuePoller::UpdateChannel(int fd, uint filter, uint old_filter) {
        PollEvent poll_event;
        if ((filter ^ old_filter) & EF_READ){
            if (filter & EF_READ){
                EV_SET(&poll_event, fd, EVFILT_READ, EV_ADD, 0, 0, NULL);
                int ret = kevent(kqueue_fd_, &poll_event, 1, NULL, 0, NULL);
                if (ret < 0) {
                    LOG_ERROR << fd << "Channel add failed" << strerror(errno);
                }
            }
            else {
                EV_SET(&poll_event, fd, EVFILT_READ, EV_DELETE, 0, 0, NULL);
                int ret = kevent(kqueue_fd_, &poll_event, 1, NULL, 0, NULL);
                if (ret < 0) {
                    LOG_ERROR << fd << "Channel change failed" << strerror(errno);
                }
            }
        }

        if ((filter ^ old_filter) & EF_WRITE) {
            if (filter & EF_WRITE) {
                EV_SET(&poll_event, fd, EVFILT_WRITE, EV_ADD, 0, 0, NULL);
                int ret = kevent(kqueue_fd_, &poll_event, 1, NULL, 0, NULL);
                if (ret < 0) {
                    LOG_ERROR << fd << "Channel add failed" << strerror(errno);
                }
            }
            else {
                EV_SET(&poll_event, fd, EVFILT_WRITE, EV_DELETE, 0, 0, NULL);
                int ret = kevent(kqueue_fd_, &poll_event, 1, NULL, 0, NULL);
                if (ret < 0) {
                    LOG_ERROR << fd << "Channel add failed" << strerror(errno);
                }
            }
        }
    }

    void KqueuePoller::DeleteChannel(int fd) {
        PollEvent poll_event;
        EV_SET(&poll_event, fd, 0, EV_DELETE, 0, 0, NULL);

        int ret = kevent(kqueue_fd_, &poll_event, 1, NULL, 0, NULL);
        if (ret < 0) {
            LOG_ERROR << fd << "event delete failed" << strerror(errno);
        }
    }

    int KqueuePoller::Poll(int time_out) {

        timespec time_sec = {time_out, 0};
        int ret = kevent(kqueue_fd_, NULL, 0, events_ready_.data(), MAX_READY_EVENTS_NUM, &time_sec);
        if (ret < 0) {
            LOG_ERROR << "kevent poll error occured. " << strerror(errno);
            return -2;
        }
        return ret;
    }

    void KqueuePoller::HandleEvents(
            const int& events_ready_amount,
            const std::map<int, std::pair<uint, Channel*>>& channel_map
    ) {

        LOG_TRACE << "handling events";

        // Merge events on same fd
        std::map<int, uint> events_merged;

        for (int i = 0; i < events_ready_amount; ++i) {
            PollEvent& event = events_ready_[i];
            int fd = static_cast<int>(event.ident);
            int filter = 0;
            filter |= event.filter == EVFILT_READ ? EF_READ : 0;
            filter |= event.filter == EVFILT_WRITE ? EF_WRITE : 0;
            filter |= (event.flags & EV_EOF) == EV_EOF ? EF_CLOSE : 0;

            auto iter = events_merged.find(fd);
            if(iter == events_merged.end()) {
                events_merged[fd] = filter;
            }
            else {
                iter->second = iter->second | filter;
            }
        }

        LOG_TRACE << "Merged " << events_ready_amount << " events into " << events_merged.size() << " events.";

        for (auto event_iter: events_merged) {

            LOG_TRACE << "Event fd: " << event_iter.first;
            LOG_TRACE << "Event filter: " << event_iter.second;

            auto iter = channel_map.find(event_iter.first);
            if (iter == channel_map.end()) {
                LOG_ERROR << event_iter.first << "event not found";
            }
            auto pair = iter->second;
            pair.second->Process(Event(
                    event_iter.first,
                    event_iter.second
            ));
        }
    }


}
