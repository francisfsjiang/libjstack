#ifndef _ABATHUR_UTIL_TIMER_HPP_
#define _ABATHUR_UTIL_TIMER_HPP_

#include <functional>

namespace abathur::util {
    enum TimerType{
        EVERY,
        ONCE
    };

    class Timer {
    private:
        int time_;
        int interval_;
        bool canceled_;
        std::function<int(int)> func_;
        TimerType type_;
    public:
        Timer(int, TimerType, int, std::function<int(int)>);
        ~Timer();

        int get_time();
        int set_time(int);

        int get_interval();

        int process(int);

        void cancel();

        bool canceled();

        TimerType get_type();

    };

    int get_time();
    std::string get_datetime();
}


#endif //_ABATHUR_UTIL_TIMER_HPP_
