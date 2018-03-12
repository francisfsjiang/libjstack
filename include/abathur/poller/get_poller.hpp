#ifndef _ABATHUR_POLLER_GETPOLLER_HPP_
#define _ABATHUR_POLLER_GETPOLLER_HPP_

#if defined(ABATHUR_LINUX)

#include "abathur/poller/epoll_poller.h"

#elif defined(ABATHUR_DARWIN) || defined(ABATHUR_UNIX)

#include "abathur/poller/kqueue_poller.hpp"

#endif

namespace abathur {
namespace poller {


#if defined(ABATHUR_LINUX)

class EpollPoller;

EpollPoller* GetPoller();

#elif defined(ABATHUR_DARWIN) || defined(ABATHUR_UNIX)

class KqueuePoller;

KqueuePoller *GetPoller();

#endif


}
}

#endif //_ABATHUR_GETPOLLER_HPP_
