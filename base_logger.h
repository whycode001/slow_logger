#ifndef SLOWLOGGER_BASELOGGER_H
#define SLOWLOGGER_BASELOGGER_H

#include <string>
#include <memory>
#include <map>
#include <mutex>

#include "log_def.h"
#include "appender.h"
#include "util/base_def.h"

namespace slow_logger{

class BaseLogger
{
public:
    BaseLogger(const std::string &logger_name);
    ~BaseLogger();
public:
    int InitLogger(const PropertiesMap &prop_map);
    void AddAppender(const std::string &appender_name, SharedAppenderPtr appender_ptr);
    void DelAppender(const std::string &appender_name);
    void LogOut(LogLevel ll, const std::string& msg);

private:
    void LogOut(const LogRecord &rec);

private:
    std::map<std::string, SharedAppenderPtr> _appender_map;
    std::mutex _mtx;
    std::string logger_name;
};


typedef std::shared_ptr<BaseLogger> SharedBaseLoggerPtr;
}

#endif
