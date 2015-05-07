#pragma once
#include <string>

class StringUtil
{
public:
    static std::string replace(std::string str, const std::string& from, const std::string& to)
    {
        size_t start_pos = str.find(from);
        if(start_pos == std::string::npos)
            return str;
        str.replace(start_pos, from.length(), to);
        return str;
    }
};
