#ifndef SLOWLOGGER_LOGFILE_H
#define SLOWLOGGER_LOGFILE_H

#include <string>
#include <iostream>
#include <fstream>

#include "util/mem_helper.h"

namespace slow_logger{

class LogFile
{
    UNCOPYABLE(LogFile);

public:
    LogFile();
    ~LogFile();
public:
    int Open(const std::string& file_name);
    int Write(const std::string &msg);
    int Rotate();
    int GetFileSize();

private:
    std::fstream _the_file;
    std::string _file_name;
};

}
#endif

