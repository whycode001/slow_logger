#ifndef SLOWLOGGER_AppenderFactory_H
#define SLOWLOGGER_AppenderFactory_H

#include <mutex>

namespace slow_logger{

class AppenderFactory
{
public:
    void static InitAppender(const std::string& log_name, int max_file_size);

private:
    static const int kMaxFileSize = 1024 * 1024 * 1024; 
};

}

#endif
