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
            LOG_DEBUG << "fd" << kqueue_fd_ << " Kqueue created.";
#endif
        }

        KqueuePoller::~KqueuePoller() {
#if defined(ABATHUR_DEBUG)
            LOG_DEBUG << "fd" << kqueue_fd_ << " Kqueue destoried.";
#endif
        }

        void KqueuePoller::AddChannel(int fd) {
            PollEvent poll_event;
            EV_SET(&poll_event, fd, EVFILT_READ, EV_ADD, 0, 0, NULL);
            EV_SET(&poll_event, fd, EVFILT_WRITE, EV_ADD, 0, 0, NULL);
            int ret = kevent(kqueue_fd_, &poll_event, 1, NULL, 0, NULL);
            if (ret < 0) {
                LOG_ERROR << fd << "Channel add failed" << strerror(errno);
            }

            LOG_DEBUG << "fd" << fd << " Kqueue add event";
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
            }
            return ret;
        }

        void KqueuePoller::HandleEvents(
                const int& events_ready_amount,
                const std::map<int, std::shared_ptr<Channel>>& channel_map
        ) {

            LOG_DEBUG << "handling events";

            for (int i = 0; i < events_ready_amount; ++i) {

                LOG_DEBUG << "event " << i << " fd: " << events_ready_[i].ident;
                LOG_DEBUG << "event " << i << " data: " << events_ready_[i].data;

                PollEvent& event = events_ready_[i];

                auto iter = channel_map.find(static_cast<int>(event.ident));
                if (iter == channel_map.end()) {
                    LOG_ERROR << event.ident << "event not found";
                }
                iter->second->Process(Event(
                        event.ident,
                        event.filter == EVFILT_READ,
                        event.filter == EVFILT_WRITE,
                        (event.flags & EV_EOF) == EV_EOF
                ));
//                if (iter->second.HasCloseCallback() &&
//                    ) {
//                    iter->second.ExecCloseCallback(event.ident,
//                                                   event.data);
//                }
//                else if () {
//                    iter->second.ExecReadCallback(event.ident,
//                                                  event.data);
//                }
//                else if () {
//                    iter->second.ExecWriteCallback(event.ident,
//                                                   event.data);
//                }

            }
        }


}