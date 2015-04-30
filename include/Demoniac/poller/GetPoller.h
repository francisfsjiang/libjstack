//
// Created by Neveralso on 15/3/18.
//

#ifndef _DEMONIAC_GETPOLLER_H_
#define _DEMONIAC_GETPOLLER_H_

#if defined(__linux__)

#include "Demoniac/poller/EpollPoller.h"

#elif defined(__unix__) || defined(__MACH__)

#include "Demoniac/poller/KqueuePoller.h"

#endif

namespace dc {

#if defined(__linux__)

class EpollPoller;

EpollPoller* GetPoller();

#elif defined(__unix__) || defined(__MACH__)

class KqueuePoller;

KqueuePoller *GetPoller();

#endif

}

#endif //_DEMONIAC_GETPOLLER_H_
