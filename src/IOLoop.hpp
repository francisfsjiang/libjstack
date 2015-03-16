//
// Created by Neveralso on 15/3/15.
//

#ifndef _DEMONIAC_IOLOOP_H_
#define _DEMONIAC_IOLOOP_H_

#include <pthread.h>

//#include "noncopyable.hpp"

namespace dc {

    class IOLoop {
    private:
        IOLoop* _instance;
    public:
        IOLoop();
    };

}


#endif //_DEMONIAC_IOLOOP_H_
