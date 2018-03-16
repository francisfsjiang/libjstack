#include "abathur/log.hpp"

#include <iostream>
#include <unistd.h>

namespace abathur {

    std::string get_date() {
        char buffer[80];
        time_t te = time(NULL);
        strftime(buffer, 80, "%m-%d-%Y %H:%M:%S", gmtime(&te));
        return std::string(buffer);
    }

//    Log Log::Instance("dc.log");
    Log* Log::Instance = new Log();

    Log::Log() {
//        out_stream_ = new std::ofstream(std::string("abathur_") + get_date() + ".log");
        out_stream_ = &std::cout;
        buffer_ = new char[80];
    }

    Log::Log(std::string file) {
        out_stream_ = new std::ofstream(file);
        buffer_ = new char[80];
    }

    std::string Log::get_date() {
        time_t te = time(NULL);
        strftime(buffer_, 80, "%m-%d-%Y %H:%M:%S", gmtime(&te));
        return std::string(buffer_);
    }

    std::string get_level(LogLevel level) {
        switch (level) {
            case TRACE:
                return "TRACE";
            case DEBUG:
                return "DEBUG";
            case INFO:
                return "INFO";
            case WARNING:
                return "WARNING";
            case ERROR:
                return "ERROR";
            case FATAL:
                return "FATAL";
            default:
                return "NO_LOG";
        }
    }

    std::ostream &Log::log(LogLevel level) {
        log_level_ = level;
        *out_stream_
                << std::endl
                << get_pid()
                << " "
                << get_date()
                << " "
                << get_level(level)
                << " ";
        return *out_stream_;
    }

    int Log::get_pid() {
        return getpid();
    }

    std::ostream &Log::log(int i) {
        return Log::log((LogLevel) i);
    }

    Log::~Log() {
        *out_stream_ << std::endl;
    }


}