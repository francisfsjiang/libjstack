//
// Created by Neveralso on 15/3/17.
//

#ifndef _DEMONIAC_EPOLLPOLLER_H_
#define _DEMONIAC_EPOLLPOLLER_H_

#include "Poller.h"

#include <sys/epoll.h>

namespace dc {

class EpollPoller : public Poller {
private:
public:

    typedef epoll_event poll_event;

};

}


#endif //_DEMONIAC_EPOLLPOLLER_H_
