//
// Created by Neveralso on 15/3/17.
//

#ifndef _DEMONIAC_EVENT_CALLBACK_H_
#define _DEMONIAC_EVENT_CALLBACK_H_

#include <functional>

namespace demoniac {


class EventCallback {
private:

    typedef std::function<void(const int&, const int&)> CallbackFunction;

    CallbackFunction  read_callback_ = nullptr;
    CallbackFunction write_callback_ = nullptr;
    CallbackFunction error_callback_ = nullptr;
    CallbackFunction close_callback_ = nullptr;

public:
    EventCallback();

    ~EventCallback();

    int GetFD() const;

    void  SetReadCallback(CallbackFunction  read_callback);
    bool  HasReadCallback() const;
    void ExecReadCallback(const int& fd, const int& data) const;

    void  SetWriteCallback(CallbackFunction write_callback);
    bool  HasWriteCallback() const;
    void ExecWriteCallback(const int& fd, const int& data) const;

    void  SetErrorCallback(CallbackFunction error_callback);
    bool  HasErrorCallback() const;
    void ExecErrorCallback(const int& fd, const int& data)const;

    void  SetCloseCallback(CallbackFunction close_callback);
    bool  HasCloseCallback() const;
    void ExecCloseCallback(const int& fd, const int& data) const;
};

}

#endif //_DEMONIAC_EVENT_H_
