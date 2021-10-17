#ifndef SLOWLOGGER_ROLLAPPENDER_H
#define SLOWLOGGER_ROLLAPPENDER_H

#include <mutex>

#include "appender.h"
#include "log_def.h"
#include "log_file.h"
#include "util/mem_helper.h"

namespace slow_logger{

class RollAppender: public IAppender
{
    UNCOPYABLE(RollAppender);

public:
    RollAppender();
    ~RollAppender();

public:
    virtual int Init(const std::string& file_name, long max_file_size);
    virtual bool NeedWrite(int flag);
    virtual void WriteLog(const LogRecord& rec);

private:
    int  OpenFile();
    bool RollFile();

    int ToMsg(const LogRecord& rec, std::string &msg);

private:
    bool _is_open_file;
    std::string _file_name;
    LogFile _log_file;

    int _log_level;
    
    bool _is_lock_file;
    std::mutex _mtx;
    
    long _max_file_size;
};

typedef std::shared_ptr<RollAppender> SharedRollAppenderPtr;
}

#endif
