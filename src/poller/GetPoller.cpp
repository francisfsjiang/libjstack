//
// Created by Neveralso on 15/3/18.
//

#include "Demoniac/poller/GetPoller.h"



namespace dc {

#if defined(__linux__)

EpollPoller* GetPoller() {
    return new EpollPoller();
}

#elif defined(__unix__) || defined(__MACH__)

KqueuePoller *GetPoller() {
    return new KqueuePoller();
}

#endif


}