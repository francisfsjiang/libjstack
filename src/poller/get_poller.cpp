#include "abathur/poller/get_poller.h"



namespace abathur {
namespace poller {

#if defined(ABATHUR_LINUX)

EpollPoller* GetPoller() {
    return new EpollPoller();
}

#elif defined(ABATHUR_DARWIN) || defined(ABATHUR_UNIX)

KqueuePoller *GetPoller() {
    return new KqueuePoller();
}

#endif


}
}