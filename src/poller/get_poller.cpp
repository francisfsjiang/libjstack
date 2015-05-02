//
// Created by Neveralso on 15/3/18.
//

#include "demoniac/poller/get_poller.h"



namespace demoniac {
namespace poller {

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
}