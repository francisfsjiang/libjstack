//
// Created by Neveralso on 15/3/17.
//

#ifndef _DEMONIAC_LOG_H_
#define _DEMONIAC_LOG_H_


#define LOG_DEBUG dc::Log::Instance.log(0)
#define LOG_INFO dc::Log::Instance.log(1)
#define LOG_WARNING dc::Log::Instance.log(2)
#define LOG_ERROR dc::Log::Instance.log(3)
#define LOG_CRITICAL dc::Log::Instance.log(4)

#include <fstream>

namespace dc {

enum LogLevel {
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    CRITICAL,
};

class Log {  //TODO a fast security logger
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

    std::ofstream& log(int i);

    std::ofstream& log(LogLevel level);

};


}

#endif //_DEMONIAC_LOG_H_
