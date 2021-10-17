#include "string_util.h"

std::vector<std::string> StringUtil::split(const std::string& s, const std::string& seperator)
{
    std::vector<std::string> result;
    typedef std::string::size_type string_size;
    string_size i = 0;

    while(i != s.size())
    {
        int flag = 0;
        while(i != s.size() && flag == 0)
        {
            flag = 1;
            for(string_size x = 0; x < seperator.size(); ++x)
            {
                if(s[i] == seperator[x])
                {
                    ++i;
                    flag = 0;
                    break;
                }
            }
        }

        flag = 0;
        string_size j = i;
        while(j != s.size() && flag == 0)
        {
            for(string_size x = 0; x < seperator.size(); ++x)
            {
                if(s[j] == seperator[x])
                {
                    flag = 1;
                    break;
                }
            }
            if(flag == 0)
            {
                ++j;
            }
        }
        if(i != j)
        {
            result.push_back(s.substr(i, j-i));
            i = j;
        }
    }
    return result;
}

bool StringUtil::isNum(const std::string& str)
{
    if (str.size() > 64 && str.empty())
    {
        return false;
    }
    
    for(size_t i = 0; i < str.size(); ++i)
    {
        if (isdigit(str[i]) == 0)
        {
            return false;
        }
    }
    return true;
}

void StringUtil::replace(std::string& str,const std::string& old_value, const std::string& new_value)
{
    for (std::string::size_type pos(0); pos != std::string::npos; pos+=new_value.length())
    {
        if ((pos = str.find(old_value, pos)) != std::string::npos)
        {
            str.replace(pos, old_value.length(), new_value);
        }
        else
        {
            break;
        }
    }
}

std::string StringUtil::getTwoDecimalString(const std::string& s)
{
    auto pos = s.find('.');
    if(pos == std::string::npos)
    {
        return "0";
    }
    return s.substr(0, pos + 3);
}
