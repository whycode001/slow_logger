#include <thread>
#include <unistd.h>
#include <vector>
#include <string>
#include <iostream>

#include "logger_factory.h"
#include "base_logger.h"
#include "log_def.h"

using namespace std;
using namespace slow_logger;

struct TestDef
{
    int log_seq;
    SharedBaseLoggerPtr logger_ptr;
};

extern SharedBaseLoggerPtr g_logger;

SharedBaseLoggerPtr g_logger;
void testLog(void* data)
{
    if(data == nullptr)
    {
        return;
    }

    string content = "test:";

    const TestDef& test_def = *(TestDef*) data;
    // SharedBaseLoggerPtr cur_logger = test_def.logger_ptr;
    int log_seq = test_def.log_seq;
    content += to_string(log_seq);
    LOG_INFO(content);
}

int main()
{
    string log_conf_file = "log.conf";
    LoggerFactory::Init(log_conf_file);

    g_logger = LoggerFactory::GetLogger("root");

    static const int kTidNum = 32;
    vector<TestDef> test_defs;
    for(int i = 0; i < kTidNum; i ++)
    {
        TestDef test_def;
        test_def.log_seq  = i;
        test_def.logger_ptr = g_logger;
        test_defs.push_back(test_def);
    }
    // for(int i = 0; i < kTidNum; i ++)
    // {
    //     test_defs[i].logger_ptr-> LogOut(INFO, "content");
    // }

    vector<thread> tids;
    for(int i = 0; i < kTidNum; i ++)
    {
        std::thread tid(testLog, &(test_defs[i]));
        tids.push_back(std::move(tid));
    }

    for(int i = 0; i < kTidNum; i ++)
    {
        tids[i].join();
    }

    sleep(2);
    cout << "exit!" << endl;
}

