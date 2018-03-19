#include "abathur/log.hpp"

#include <iostream>
#include <unistd.h>

#include "abathur/util/timer.hpp"

namespace abathur {

//    Log* Log::Instance = new Log("dc.log");
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
        return util::get_datetime();
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

    Logger Log::log(LogLevel level) {
        log_level_ = level;
        *out_stream_
                << get_pid()
                << " "
                << get_date()
                << " "
                << get_level(level)
                << " ";
        return Logger(out_stream_);
    }
    Logger Log::log(int i) {
        return Log::log((LogLevel) i);
    }

    int Log::get_pid() {
        return getpid();
    }


    Log::~Log() {
//        *out_stream_ << std::endl;
    }

    Logger::Logger(std::ostream* ostream) {
        ostream_ = ostream;
    }

    Logger::~Logger() {
        *ostream_ << std::endl;
    }

    Logger& Logger::operator<<(const char* data) {
        *ostream_ << data;
        return *this;
    }

    Logger& Logger::operator<<(int data) {
        *ostream_ << data;
        return *this;
    }
    Logger& Logger::operator<<(const std::string& data) {
        *ostream_ << data;
        return *this;
    }

    Logger& Logger::operator<<(void* data) {
        *ostream_ << data;
        return *this;
    }
}