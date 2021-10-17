#ifndef SLOWLOGGER_FILEREADER_H
#define SLOWLOGGER_FILEREADER_H

#include <string>
#include "base_def.h"

namespace slow_logger{

class FileReader
{
private:
    FileReader(){}
    ~FileReader(){}

public:
    static int ReadFromFile(const std::string &file_name, PropertiesMap &prop_map);

public:
    static const int kReadOK = 0;
    static const int kReadERR = -1;
};

}

#endif