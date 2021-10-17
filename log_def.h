#ifndef SLOWLOGGER_LOGDEF_H
#define SLOWLOGGER_LOGDEF_H

#include <string>

namespace slow_logger{
// static const char* LogStr[] = {"DEBUG", "INFO", "WARN", "ERROR"};
enum LogLevel{
    DEBUG = 0,
    INFO  = 1,
    WARN  = 2,
    ERROR = 3
};

#define SL_LOG(logger, level, msg) \
    logger->LogOut(level, msg);
 
#define LOG_DEBUG(msg) SL_LOG(g_logger, DEBUG, msg);
#define LOG_INFO(msg)  SL_LOG(g_logger, INFO,  msg);
#define LOG_WARN(msg)  SL_LOG(g_logger, WARN,  msg);
#define LOG_ERROR(msg) SL_LOG(g_logger, ERROR, msg);

struct ErrDef
{
    static const int kOK = 0;
    static const int kFileERR = -1;
    static const int kOutErr = -2;


    static const int kConfKeyErr = -3;


};

struct LogRecord 
{
    LogLevel ll;
    std::string msg;
};

}

#endif
