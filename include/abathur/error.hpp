#ifndef _ABATHUR_ERROR_HPP_
#define _ABATHUR_ERROR_HPP_

#include <string>
#include <exception>

using namespace std;

namespace abathur {


    class BaseError: std::exception {
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

    class IllegalIPAddressError: public BaseError {
    public:
        IllegalIPAddressError(string e) : BaseError(e) {
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


#endif //_ABATHUR_ERROR_HPP_
