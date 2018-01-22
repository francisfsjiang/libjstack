#ifndef _ABATHUR_POLLER_KQUEUEPOLLER_H_
#define _ABATHUR_POLLER_KQUEUEPOLLER_H_

#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>


#include "abathur/abathur.h"

#include "abathur/poller/poller.h"

namespace abathur {
namespace poller {


class KqueuePoller : public Poller {
private:
    typedef struct kevent PollEvent;

    int kqueue_fd_;

    std::vector<PollEvent> events_ready_;

public:
    KqueuePoller();

    virtual ~KqueuePoller() override ;

    virtual int Poll(int time_out) override ;

    virtual void HandleEvents(const int& events_ready_amount, const std::map<int, EventCallback>& events_map) override ;

    virtual void AddEventCallback(const int& fd, const EventCallback& e) override ;

    virtual void UpdateEventCallback(const int& fd, const EventCallback& e) override ;

    virtual void DeleteEventCallback(const int& fd) override ;
};


}
}


#endif //_ABATHUR_KQUEUEPOLLER_H_
