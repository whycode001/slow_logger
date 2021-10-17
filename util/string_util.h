#ifndef _STRING_UTIL_H_
#define _STRING_UTIL_H_

#include <string>
#include <vector>

class StringUtil
{
public:
    static std::vector<std::string> split(const std::string& s, const std::string& seperator);
    static bool isNum(const std::string& str);
    static void replace(std::string& str,const std::string& old_value, const std::string& new_value);
    static std::string getTwoDecimalString(const std::string& s);
};

#endif