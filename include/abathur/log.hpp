#ifndef _ABATHUR_LOG_HPP_
#define _ABATHUR_LOG_HPP_

#include <fstream>

#include <errno.h>

namespace abathur {

    enum LogLevel {
        NO_LOG,
        TRACE,
        DEBUG,
        INFO,
        WARNING,
        ERROR,
        FATAL,
    };

#if defined(ABATHUR_DEBUG)
    #define LOG_TRACE abathur::Log::Instance->log(TRACE)
    #define LOG_DEBUG abathur::Log::Instance->log(DEBUG)
#else
    #define LOG_TRACE abathur::Log::Instance->log(TRACE)
    #define LOG_DEBUG abathur::Log::Instance->log(DEBUG)
#endif
    #define LOG_INFO     abathur::Log::Instance->log(INFO)
    #define LOG_WARNING  abathur::Log::Instance->log(WARNING)
    #define LOG_ERROR    abathur::Log::Instance->log(ERROR)
    #define LOG_FATAL    abathur::Log::Instance->log(FATAL)

    class Logger;

    class Log {  //TODO a fast logger
    public:

        static Log* Instance;

        std::ostream *out_stream_;

        std::string get_date();

        int get_pid();

        char *buffer_;

        LogLevel log_level_ = TRACE;

        Log();
        Log(std::string file);

        ~Log();

//        std::ostream &log(int i);
//        std::ostream &log(LogLevel level);

        Logger log(int i);
        Logger log(LogLevel level);
    };

    class Logger{
    private:
        std::ostream* ostream_;
    public:
        Logger(std::ostream*);
        ~Logger();
        Logger& operator<< (int);
        Logger& operator<< (const char*);
        Logger& operator<< (const std::string&);
        Logger& operator<< (void*);
    };



}

#endif //_ABATHUR_LOG_HPP_
