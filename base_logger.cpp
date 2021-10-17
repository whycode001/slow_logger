#include "base_logger.h"

#include <string>
#include <iostream>
#include "util/base_def.h"
#include "appender.h"
#include "roll_appender.h"

using namespace std;
using namespace slow_logger;

namespace slow_logger{

BaseLogger::BaseLogger(const string &logger_name)
{
    this->logger_name = logger_name;
}

BaseLogger::~BaseLogger()
{
    cerr << "BaseLogger destructor" << endl;
}

int BaseLogger::InitLogger(const PropertiesMap &prop_map)
{
    PropertiesMap::const_iterator log_appender_it = prop_map.find("log_appender");
    if (log_appender_it == prop_map.end())
    {
        cerr << "has no key:log_appender!"<< endl;
        return ErrDef::kConfKeyErr;
    }

    PropertiesMap::const_iterator file_name_it = prop_map.find("log_file_name");
    if (file_name_it == prop_map.end())
    {
        cerr << "has no key:log_file_name!"<< endl;
        return ErrDef::kConfKeyErr;
    }

    PropertiesMap::const_iterator max_file_size_it = prop_map.find("max_file_size");
    if (max_file_size_it == prop_map.end())
    {
        cerr << "has no key:max_file_size!"<< endl;
        return ErrDef::kConfKeyErr;
    }

    const string &appender_name = log_appender_it -> second;
    const string &file_name = file_name_it -> second;
    long max_file_size = stol(max_file_size_it -> second);

    if (_appender_map.find(appender_name) != _appender_map.end())
    {
        _appender_map.erase(appender_name);
    }
    
    SharedAppenderPtr shared_appender_ptr;
    if (appender_name == "RollAppender")
    {
        shared_appender_ptr = make_shared<RollAppender>();
    }

    shared_appender_ptr -> Init(file_name, max_file_size);
    AddAppender(appender_name, shared_appender_ptr);
    return ErrDef::kOK;
}

void BaseLogger::AddAppender(const string &appender_name, SharedAppenderPtr appender_ptr)
{
    lock_guard<mutex> lock(_mtx);
    _appender_map[appender_name] = appender_ptr;
}

void BaseLogger::DelAppender(const string &appender_name)
{
    lock_guard<mutex> lock(_mtx);
    if (_appender_map.find(appender_name) != _appender_map.end())
    {
        _appender_map.erase(appender_name);
    }
}

void BaseLogger::LogOut(LogLevel ll, const std::string& msg)
{
    LogRecord log_rec;
    log_rec.ll = ll;
    log_rec.msg = msg;
    
    cout << "msg:" << msg << endl;
    LogOut(log_rec);
}

void BaseLogger::LogOut(const LogRecord &rec)
{
    map<string, SharedAppenderPtr>::iterator it =  _appender_map.begin(); 
    for(; it != _appender_map.end(); it ++)
    {
        (it->second)->WriteLog(rec);
    }
}

}
