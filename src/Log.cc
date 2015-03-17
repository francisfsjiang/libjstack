//
// Created by Neveralso on 15/3/17.
//

#include "Log.h"

#include <ctime>
#include <unistd.h>

namespace dc {

Log Log::Instance("dc.log");

Log::Log(std::string file) {
    out_stream_ = new std::ofstream(file);
    buffer_ = new char[80];
}

std::string Log::get_date() {
    time_t te = time(NULL);
    strftime(buffer_, 80, "%m-%d-%Y %H:%M:%S",gmtime(&te));
    return std::string(buffer_);
}

std::string Log::get_level() {
    switch (log_level_) {
        case DEBUG:
            return "DEBUG";
        case INFO:
            return "INFO";
        case WARNING:
            return "WARNING";
        case ERROR:
            return "ERROR";
        case CRITICAL:
            return "CRITICAL";
    }
}

std::ofstream &Log::log(LogLevel level) {
    log_level_ = level;
    *out_stream_
            <<std::endl
            <<get_pid()
            <<" "
            <<get_date()
            <<" "
            <<get_level()
            <<" ";
    return *out_stream_;
}

int Log::get_pid() {
    return getpid();
}

std::ofstream &Log::log(int i) {
    return Log::log((LogLevel)i);
}

Log::~Log() {
    *out_stream_<<std::endl;
}

}