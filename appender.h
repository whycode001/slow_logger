#ifndef SLOWLOGGER_IAPPENDER_H
#define SLOWLOGGER_IAPPENDER_H

#include <memory>

#include "log_def.h"

namespace slow_logger{
    
class IAppender
{
public:
    virtual int Init(const std::string& file_name, long max_file_size) = 0;
    virtual bool NeedWrite(int flag) = 0; 
    virtual void WriteLog(const LogRecord& rec) = 0; 
};

typedef std::shared_ptr<IAppender> SharedAppenderPtr;
}

#endif
