#ifndef SLOWLOGGER_LOGGERTHREAD_H
#define SLOWLOGGER_LOGGERTHREAD_H

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <mutex>


#include "base_logger.h"

namespace slow_logger{

class LoggerThread
{
public:
    LoggerThread();
    ~LoggerThread();

public:
    void AddLogger(const BaseLogger* ptr);
    void DelLogger(const BaseLogger* ptr);

    int Flush();
    int Run();
    int Stop();

protected:
    struct MyCom
    {
        bool operator()(const BaseLogger* ptr1, const BaseLogger* ptr2) const
        {
            // TODO
            return ptr1 < ptr2;
        }
    };

private:
    bool _stop;

    std::set<const BaseLogger*, MyCom> _loggers;

    std::mutex _mtx;
};

}

#endif
