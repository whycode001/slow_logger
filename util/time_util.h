#ifndef SLOWLOGGER_TIMEUTIL_H
#define SLOWLOGGER_TIMEUTIL_H

#include <string>

namespace slow_logger{

class TimeUtil
{
private:
    TimeUtil(){}
    ~TimeUtil(){}

public:
    static std::string GetTimeHourStr();
};

}

#endif