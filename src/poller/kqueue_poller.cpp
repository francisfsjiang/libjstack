#include "abathur/poller/kqueue_poller.h"

#include <unistd.h>

#include "abathur/abathur.h"

#include "abathur/event_callback.h"

namespace abathur::poller {

        KqueuePoller::KqueuePoller() {
            events_ready_.resize(MAX_READY_EVENTS_NUM);
            kqueue_fd_ = kqueue();
            if (kqueue_fd_ < 0) {
                LOG_ERROR << "Kqueue init failed.";
            }
#if defined(ABATHUR_DEBUG)
            LOG_DEBUG << "fd" << kqueue_fd_ << " Kqueue created.";
#endif
        }

        KqueuePoller::~KqueuePoller() {
#if defined(ABATHUR_DEBUG)
            LOG_DEBUG << "fd" << kqueue_fd_ << " Kqueue destoried.";
#endif
        }

        void KqueuePoller::AddEventCallback(const int& fd, const EventCallback& e) {
            PollEvent poll_event;
            int ret;
            //Add read event
            if (e.HasReadCallback()) {
                EV_SET(&poll_event, fd, EVFILT_READ, EV_ADD, 0, 0, NULL);
                ret = kevent(kqueue_fd_, &poll_event, 1, NULL, 0, NULL);
                if (ret < 0) {
                    LOG_ERROR << fd << "event read add failed" << strerror(errno);
                }
            }
            //Add write event
            if (e.HasWriteCallback()) {
                EV_SET(&poll_event, fd, EVFILT_WRITE, EV_ADD, 0, 0, NULL);
                ret = kevent(kqueue_fd_, &poll_event, 1, NULL, 0, NULL);
                if (ret < 0) {
                    LOG_ERROR << fd << "event write add failed" << strerror(errno);
                }
            }

            LOG_DEBUG << "fd" << fd << " Kqueue add event";
        }

        void KqueuePoller::UpdateEventCallback(const int& fd, const EventCallback &e) {
            //readd will modify the event
            PollEvent poll_event;
            int ret;
            //Add read event
            if (e.HasReadCallback()) {
                EV_SET(&poll_event, fd, EVFILT_READ, EV_ADD, 0, 0, NULL);
                ret = kevent(kqueue_fd_, &poll_event, 1, NULL, 0, NULL);
                if (ret < 0) {
                    LOG_ERROR << fd << "event read modify failed" << strerror(errno);
                }
            }
            //Add write event
            if (e.HasWriteCallback()) {
                EV_SET(&poll_event, fd, EVFILT_WRITE, EV_ADD, 0, 0, NULL);
                ret = kevent(kqueue_fd_, &poll_event, 1, NULL, 0, NULL);
                if (ret < 0) {
                    LOG_ERROR << fd << "event write modify failed" << strerror(errno);
                }
            }
        }

        void KqueuePoller::DeleteEventCallback(const int& fd) {
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
            }
            return ret;
        }

        void KqueuePoller::HandleEvents(const std::map<int, EventCallback>& events_map) {

            LOG_DEBUG << "handling events";

            for (int i = 0; i < events_ready_amount_; ++i) {

                LOG_DEBUG << "event " << i << " fd: " << events_ready_[i].ident;
                LOG_DEBUG << "event " << i << " data: " << events_ready_[i].data;

                auto iter = events_map.find(static_cast<int>(events_ready_[i].ident));
                if (iter == events_map.end()) {
                    LOG_ERROR << events_ready_[i].ident << "event not found";
                }
                if (iter->second.HasCloseCallback() &&
                    (events_ready_[i].flags & EV_EOF) == EV_EOF) {
                    iter->second.ExecCloseCallback(events_ready_[i].ident,
                                                   events_ready_[i].data);
                }
                else if (events_ready_[i].filter == EVFILT_READ) {
                    iter->second.ExecReadCallback(events_ready_[i].ident,
                                                  events_ready_[i].data);
                }
                else if (events_ready_[i].filter == EVFILT_WRITE) {
                    iter->second.ExecWriteCallback(events_ready_[i].ident,
                                                   events_ready_[i].data);
                }

            }
        }


}