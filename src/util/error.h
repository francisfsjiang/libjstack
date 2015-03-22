//
// Created by Neveralso on 15/3/16.
//

#ifndef _DEMONIAC_ERROR_H_
#define _DEMONIAC_ERROR_H_

#include <string>

#include "noncopyable.h"

using namespace std;

namespace dc {
class BaseError {
protected:
    string event;
public:
    BaseError(string e);
};

class IOLoopConstructorError : public BaseError {
public:
    IOLoopConstructorError(string e);
};

class SocketError : public BaseError {
public:
    SocketError(string e);
};

class IllegalFunctionError : public BaseError {
public:
    IllegalFunctionError(string e);
};

class NotSupportYetError : public BaseError {
public:
    NotSupportYetError(string e);
};

}


#endif //_DEMONIAC_ERROR_H_
