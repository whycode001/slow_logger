#include "file_reader.h"
#include <fstream>
#include <iostream>
#include <vector>

#include "string_util.h"

using namespace std;

namespace slow_logger{

int FileReader::ReadFromFile(const string &file_name, PropertiesMap &prop_map)
{
    fstream file_in(file_name);
    if (!file_in.is_open())
    {
        return FileReader::kReadERR;
    }

    string one_line = "";
    while (std::getline(file_in, one_line))
    {
        if (one_line.at(0) == '#')
        {
            continue;
        }
        cout << "line:" << one_line << endl;
        vector<string> tmp_vec = StringUtil::split(one_line, "=");
        if (tmp_vec.size() != 2)
        {
            continue;
        }

        prop_map[tmp_vec[0]] = tmp_vec[1];
    }
    return FileReader::kReadOK;
}

}
