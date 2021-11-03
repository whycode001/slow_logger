#include "log_file.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <cerrno>
#include <cstring>
#include <system_error>

#include "log_def.h"
#include "util/time_util.h"

using namespace std;
using namespace slow_logger;

namespace slow_logger{

LogFile::LogFile()
{
}

LogFile::~LogFile()
{
    if (_the_file.is_open())
    {
        _the_file.close();
    }
}

int LogFile::Open(const string& file_name)
{
    if(file_name.empty())
    {
        cerr << "file_name empty!!" << file_name;
        return ErrDef::kFileERR;
    }

    _file_name = file_name;
    _the_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {    
        _the_file.open(_file_name, ios::out | ios::ate | ios::app);
    }
    catch (std::system_error& e) 
    {
        cerr << "open file err:" << e.code().message() << std::endl;
        return ErrDef::kFileERR;
    }

    if(!_the_file.is_open())
    {
        cerr << "can't open file:" << _file_name << std::endl;
        return ErrDef::kFileERR;
    }
    return ErrDef::kOK;   
}

int LogFile::Write(const string &msg)
{
    _the_file << msg << endl;
    return ErrDef::kOK;
}

int LogFile::GetFileSize()
{
    if(!_the_file.is_open())
    {
        return ErrDef::kFileERR;
    }

    _the_file.seekp(0, std::ios_base::end);
    return _the_file.tellp();
}

//the caller should guarantee there no data is written when rotate
int LogFile::Rotate()
{
    string time_str = TimeUtil::GetTimeHourStr();
    string new_file_name = _file_name + time_str;
    rename(_file_name.c_str(), new_file_name.c_str());
    if(_the_file.is_open())
    {
        _the_file.close();
    }

    //reopen file
    _the_file.open(_file_name);
    if(!_the_file.is_open())
    {
        cerr << "open file err " << _file_name << endl;
        return ErrDef::kFileERR;
    }
    return ErrDef::kOK;
}

}
