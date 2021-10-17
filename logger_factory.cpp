#include "logger_factory.h"
#include <iostream>
#include <memory>

#include "util/file_reader.h"

using namespace std;
namespace slow_logger{

std::map<std::string, SharedBaseLoggerPtr> LoggerFactory::_logger_map;

int LoggerFactory::Init(const string &log_conf_file)
{
    PropertiesMap prop_map;
    int ret = FileReader::ReadFromFile(log_conf_file, prop_map);
    if (ret != 0)
    {
        cerr << "ReadFromFile err " << log_conf_file << ",code " << ret << endl;
        return 0;
    }
    PropertiesMM prop_mm;
    BuildPropertiesMM(prop_map, prop_mm);
    PropertiesMM::iterator it = prop_mm.begin();
    for(; it != prop_mm.end(); it ++)
    {
        const string &logger_name = it -> first;
        cout << "init logger_name:" << logger_name << endl;
        const PropertiesMap &prop_map = it -> second;
        if(_logger_map.find(logger_name) != _logger_map.end())
        {
            _logger_map.erase(logger_name);
        }
        SharedBaseLoggerPtr shared_logger_prt =  make_shared<BaseLogger>(logger_name);
        shared_logger_prt -> InitLogger(prop_map);

        AddLogger(logger_name, shared_logger_prt);
    }
    return 0;
}

SharedBaseLoggerPtr LoggerFactory::GetLogger(const string &logger_name)
{
    if (_logger_map.find(logger_name) == _logger_map.end())
    {
        cerr << "has no thie logger:" << logger_name << endl;
        return NULL;
    }
    return _logger_map[logger_name];
}

void LoggerFactory::BuildPropertiesMM(const PropertiesMap &prop_map, PropertiesMM &prop_mm)
{
    prop_mm["root"] = prop_map;
}

void LoggerFactory::AddLogger(string logger_name, SharedBaseLoggerPtr logger_ptr)
{
    _logger_map[logger_name] = logger_ptr;
}

}