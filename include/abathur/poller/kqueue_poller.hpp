#ifndef _ABATHUR_POLLER_KQUEUEPOLLER_HPP_
#define _ABATHUR_POLLER_KQUEUEPOLLER_HPP_

#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>


#include "abathur/abathur.hpp"

#include "abathur/poller/poller.hpp"

namespace abathur::poller {


    typedef struct kevent PollEvent;

    class KqueuePoller : public Poller {
    private:

        int kqueue_fd_;

        std::vector<PollEvent> events_ready_;

    public:
        KqueuePoller();

        virtual ~KqueuePoller() override ;

        virtual int Poll(int time_out) override ;

        virtual void HandleEvents(
                const int& events_ready_amount,
                const std::map<int, std::shared_ptr<Channel>>& channel_map) override ;

        virtual void AddChannel(int fd) override ;

//        virtual void UpdateChannel(const int& fd, const Channel& e) override ;

        virtual void DeleteChannel(const int& fd) override ;
    };


}


#endif //_ABATHUR_KQUEUEPOLLER_HPP_
