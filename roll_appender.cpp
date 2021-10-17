#include "roll_appender.h"

#include <iostream>
#include <mutex>

#include "log_def.h"

using namespace std;
namespace slow_logger{

RollAppender::RollAppender()
{
    _is_open_file = false;
}

RollAppender::~RollAppender()
{
    cerr << "RollAppender destructor" << endl;
}

int RollAppender::Init(const string& file_name, long max_file_size)
{
    cout << "RollAppender init " << file_name  << "," << max_file_size << endl;
    lock_guard<mutex> lock(_mtx);

    if (_is_open_file)
    {
        cout << "already open file!" << endl;
        return ErrDef::kOK;
    }

    _file_name = file_name;
    _max_file_size = max_file_size;

    _log_level = 0;
    int ret = OpenFile(); 
    if(ret != ErrDef::kOK)
    {
        cerr << "open file err " << ret << endl;
        return ErrDef::kFileERR;
    }
    _is_open_file = true;
    
    cout << "RollAppender init end!" << endl;
    return ErrDef::kOK;
}

bool RollAppender::NeedWrite(int level)
{
    return level >= _log_level;
}

void RollAppender::WriteLog(const LogRecord& rec)
{
    cout << "msg " << rec.msg << endl;
    int level = rec.ll;
    if (!NeedWrite(level))
    {
        cout << "no need write msg!" << endl;
        return;
    }

    lock_guard<mutex> lock(_mtx);
    if(!_is_open_file)
    {
        cerr << "roll_logger didn't init!!!" << endl; 
        return;
    }
    int cur_file_size = _log_file.GetFileSize();
    cout << "cur_file_size " << cur_file_size << endl;
    if(cur_file_size > _max_file_size)
    {
        bool ret = RollFile();
        if(!ret)
        {
            cerr << "roll file err, just write cur file!" << endl; 
        }
    }
    string msg = "";
    int ret = ToMsg(rec, msg);
    ret = _log_file.Write(msg);
    if(ret != ErrDef::kOK)
    {
        cerr << "write err!" << endl;
    }
}

int RollAppender::OpenFile()
{
    cout << "open file_name:" << _file_name << endl;
    int ret = _log_file.Open(_file_name);
    if(ret != ErrDef::kOK)
    {
        return ret;
    }

    return ErrDef::kOK;
}

bool RollAppender::RollFile()
{
    int ret = _log_file.Rotate();
    if(ret != ErrDef::kOK)
    {
        return false;
    }
    return true;
}

int RollAppender::ToMsg(const LogRecord& rec, string &msg)
{
    msg = rec.msg;
    return 0;
}

}
