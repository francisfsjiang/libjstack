//
// Created by Neveralso on 15/3/18.
//

#ifndef _DEMONIAC_POLLER_GETPOLLER_H_
#define _DEMONIAC_POLLER_GETPOLLER_H_

#if defined(__linux__)

#include "demoniac/poller/epoll_poller.h"

#elif defined(__unix__) || defined(__MACH__)

#include "demoniac/poller/kqueue_poller.h"

#endif

namespace demoniac {
namespace poller {


#if defined(__linux__)

class EpollPoller;

EpollPoller* GetPoller();

#elif defined(__unix__) || defined(__MACH__)

class KqueuePoller;

KqueuePoller *GetPoller();

#endif


}
}

#endif //_DEMONIAC_GETPOLLER_H_
