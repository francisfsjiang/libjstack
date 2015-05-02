//
// Created by Neveralso on 15/3/16.
//

#ifndef _DEMONIAC_UTIL_ERROR_H_
#define _DEMONIAC_UTIL_ERROR_H_

#include <string>

using namespace std;

namespace demoniac {
namespace util {


class BaseError {
protected:
    string event;
public:
    BaseError(string e) : event(e) {
    };
};

class IOLoopConstructorError : public BaseError {
public:
    IOLoopConstructorError(string e);
};

class SocketError : public BaseError {
public:
    SocketError(string e) : BaseError(e) {
    };
};

class IllegalFunctionError : public BaseError {
public:
    IllegalFunctionError(string e) : BaseError(e) {
    };
};

class EventNotFoundError : public BaseError {
public:
    EventNotFoundError(string e) : BaseError(e) {
    };
};

class HandlerTypeError : public BaseError {
public:
    HandlerTypeError(string e) : BaseError(e) {
    };
};

class PollerError : public BaseError {
public:
    PollerError(string e) : BaseError(e) {
    };
};

class NotSupportYetError : public BaseError {
public:
    NotSupportYetError(string e) : BaseError(e) {
    };
};

}
}


#endif //_DEMONIAC_ERROR_H_
