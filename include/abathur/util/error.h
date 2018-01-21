#ifndef _ABATHUR_UTIL_ERROR_H_
#define _ABATHUR_UTIL_ERROR_H_

#include <string>

using namespace std;

namespace abathur {
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


#endif //_ABATHUR_ERROR_H_
