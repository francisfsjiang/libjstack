//
// Created by Neveralso on 15/3/17.
//

#ifndef _DEMONIAC_LOG_H_
#define _DEMONIAC_LOG_H_


#define LOG_DEBUG demoniac::Log::Instance.log(0)
#define LOG_INFO demoniac::Log::Instance.log(1)
#define LOG_WARNING demoniac::Log::Instance.log(2)
#define LOG_ERROR demoniac::Log::Instance.log(3)
#define LOG_CRITICAL demoniac::Log::Instance.log(4)

#include <fstream>

#include <errno.h>

namespace demoniac {

enum LogLevel {
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    CRITICAL,
};

class Log {  //TODO a fast logger
public:

    static Log Instance;

    std::ofstream *out_stream_;

    std::string get_date();

    std::string get_level();

    int get_pid();

    char *buffer_;

    LogLevel log_level_;

    Log(std::string file = "dc.log");

    ~Log();

    std::ofstream &log(int i);

    std::ofstream &log(LogLevel level);

};


}

#endif //_DEMONIAC_LOG_H_
