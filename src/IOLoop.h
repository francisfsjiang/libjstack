//
// Created by Neveralso on 15/3/15.
//

#ifndef _DEMONIAC_IOLOOP_H_
#define _DEMONIAC_IOLOOP_H_

#include "util/noncopyable.h"

namespace dc {

    class IOLoop: noncopyable {
    private:
        IOLoop* _instance;
        bool _quit;
    public:
        IOLoop();
        void Loop();
        ~IOLoop();
    };

}


#endif //_DEMONIAC_IOLOOP_H_
