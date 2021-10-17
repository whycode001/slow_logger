#ifndef SLOWLOGGER_BASEDEF_H
#define SLOWLOGGER_BASEDEF_H

#include <string>
#include <map>

namespace slow_logger{

typedef std::map<std::string, std::string> PropertiesMap;
typedef std::map<std::string, PropertiesMap> PropertiesMM;

}

#endif
