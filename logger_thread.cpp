#include "logger_thread.h"

#include <iostream>
#include <fstream>

#include "log_def.h"

using namespace std;
namespace slow_logger{

LoggerThread::LoggerThread()
{
    _stop = false;
}

LoggerThread::~LoggerThread()
{
    _stop = true;
}

void LoggerThread::AddLogger(const BaseLogger* ptr)
{
    lock_guard<mutex> lock(_mtx);
    _loggers.insert(ptr);
}

void LoggerThread::DelLogger(const BaseLogger* ptr)
{
    lock_guard<mutex> lock(_mtx);
    _loggers.insert(ptr);
}

int LoggerThread::Flush()
{
    return ErrDef::kOK;
}

int LoggerThread::Run()
{
    while (!_stop)
    {
        
    }
    Flush();
    
    return ErrDef::kOK;
}

int LoggerThread::Stop()
{
    _stop = true;
    
    return ErrDef::kOK;
}

}
