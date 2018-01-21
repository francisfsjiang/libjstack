#ifndef _ABATHUR_EVENT_CALLBACK_H_
#define _ABATHUR_EVENT_CALLBACK_H_

#include <functional>

namespace abathur {

    typedef std::function<void(const int&, const int&)> CallbackFunction;

    class EventCallback {
    private:

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

#endif //_ABATHUR_EVENT_H_
