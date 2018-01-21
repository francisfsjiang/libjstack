#ifndef _ABATHUR_LOG_H_
#define _ABATHUR_LOG_H_

#include <fstream>

#include <errno.h>

namespace abathur {

    enum LogLevel {
        NO_LOG,
        DEBUG,
        INFO,
        WARNING,
        ERROR,
        CRITICAL,
    };

#if defined(ABATHUR_DEBUG)
    #define LOG_DEBUG abathur::Log::Instance.log(DEBUG)
#else
    #define LOG_DEBUG abathur::Log::Instance.log(NO_LOG)
#endif
    #define LOG_INFO     abathur::Log::Instance.log(INFO)
    #define LOG_WARNING  abathur::Log::Instance.log(WARNING)
    #define LOG_ERROR    abathur::Log::Instance.log(ERROR)
    #define LOG_CRITICAL abathur::Log::Instance.log(CRITICAL)


    class Log {  //TODO a fast logger
    public:

        static Log Instance;

        std::ofstream *out_stream_;

        std::string get_date();

        int get_pid();

        char *buffer_;

        LogLevel log_level_ = DEBUG;

        Log();
        Log(std::string file);

        ~Log();

        std::ofstream &log(int i);

        std::ofstream &log(LogLevel level);

    };


}

#endif //_ABATHUR_LOG_H_
