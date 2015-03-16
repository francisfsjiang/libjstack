//
// Created by Neveralso on 15/3/15.
//

#ifndef _DEMONIAC_IOLOOP_H_
#define _DEMONIAC_IOLOOP_H_

#include <pthread.h>

#include "util/noncopyable.hpp"

namespace dc {

    class IOLoop: noncopyable {
    private:
        IOLoop* _instance;
    public:
        IOLoop();
        void Loop();
    };

}


#endif //_DEMONIAC_IOLOOP_H_
