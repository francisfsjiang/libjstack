//
// Created by Neveralso on 15/3/16.
//

#ifndef _DEMONIAC_ERROR_H_
#define _DEMONIAC_ERROR_H_

#include <string>

#include "noncopyable.h"

using namespace std;

namespace dc {
class BaseError : noncopyable {
protected:
    string event;
public:
    BaseError(string e);
};

class IOLoopConstructorError : BaseError {
public:
    IOLoopConstructorError(string e);
};
}


#endif //_DEMONIAC_ERROR_H_
