#include "abathur/util/timer.hpp"

#include <string>

#include <sys/time.h>

#include "abathur/log.hpp"


namespace abathur::util {

    Timer::Timer(int time, TimerType type, int interval, std::function<int(int)> func) {
        LOG_TRACE << "Timer constructing.";
        time_ = time;
        interval_ = interval;
        func_ = func;
        type_ = type;
        canceled_ = false;
    }

    Timer::~Timer() {
        LOG_TRACE << "Timer deconstructing.";
    }

    int Timer::get_time() {
        return time_;
    }
    int Timer::set_time(int time) {
        time_ = time;
        return time_;
    }

    int Timer::get_interval() {
        return interval_;
    }

    TimerType Timer::get_type() {
        return type_;
    }

    int Timer::process(int current_time) {
        return func_(current_time);
    }

    void Timer::cancel() {
        canceled_ = true;
    }

    bool Timer::canceled() {
        return canceled_;
    }
    time_t CURRENT_TIME_T = 0;
    std::string CURRENT_DATETIME("");

    int get_time() {
        struct timeval t;
        gettimeofday(&t, NULL);
        return t.tv_sec;
    }

    std::string get_datetime() {
        char buffer[80];
        int time_sec = get_time();
        if (time_sec > CURRENT_TIME_T || CURRENT_TIME_T == 0) {
            time_t te = time(NULL);
            strftime(buffer, 80, "%m-%d-%Y %H:%M:%S\0", gmtime(&te));
            CURRENT_DATETIME = std::string(buffer);
        }
        return CURRENT_DATETIME;
    }

}