#ifndef SLOWLOGGER_LOGGERFACTORY_H
#define SLOWLOGGER_LOGGERFACTORY_H

#include <string>
#include <mutex>
#include <map>

#include "util/file_reader.h"
#include "base_logger.h"

namespace slow_logger{

class LoggerFactory
{
private:
    LoggerFactory();
    ~LoggerFactory();

public:
    static int Init(const std::string &log_conf_file);
    static SharedBaseLoggerPtr GetLogger(const std::string &logger_name);

private:
    static void BuildPropertiesMM(const PropertiesMap &prop_map, PropertiesMM &prop_mm);
    static void AddLogger(std::string logger_name, SharedBaseLoggerPtr logger_ptr);
    
private:
    static std::map<std::string, SharedBaseLoggerPtr> _logger_map;
};

}

#endif
