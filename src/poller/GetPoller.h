//
// Created by Neveralso on 15/3/18.
//

#ifndef _DEMONIAC_GETPOLLER_H_
#define _DEMONIAC_GETPOLLER_H_

#if defined(__linux__)
    #include "EpollPoller.h"
#elif defined(__unix__) || defined(__MACH__)

#include "KqueuePoller.h"

#endif

namespace dc {

#if defined(__linux__)

EpollPoller* GetPoller();

#elif defined(__unix__) || defined(__MACH__)

KqueuePoller *GetPoller();

#endif

}

#endif //_DEMONIAC_GETPOLLER_H_
