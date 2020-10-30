#include <algorithm>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

#include "../../include/tools/time.h"

void tools::time_stamp::init(unsigned short h, unsigned short m, unsigned short s, unsigned short ms)
{
    this->hour = h;
    this->minute = m;
    this->second = s;
    this->milli_second = ms;
}

void tools::time_stamp::parse_from_second(int second)
{
    this->second = second % 60;
    second /= 60;

    this->minute = second % 60;
    second /= 60;

    this->hour = second % 60;
    second /= 60;
}

void tools::time_stamp::parse_from_srt_time(std::string str)
{
    std::stringstream ss;

    ss << str.substr(0, 2);
    ss >> this->hour;

    ss.clear();
    ss << str.substr(3, 2);
    ss >> this->minute;

    ss.clear();
    ss << str.substr(6, 2);
    ss >> this->second;

    ss.clear();
    ss << str.substr(9, 3);
    ss >> this->milli_second;
}

void tools::time_stamp::parse_from_bcc_time(std::string str)
{
    size_t dot = 0;
    for (size_t i = 0; i < str.size(); i++)
    {
        if (str[i] == '.')
        {
            dot = i;
            break;
        }
    }

    std::stringstream ss;
    ss << str.substr(0, dot);
    int second;
    ss >> second;
    this->parse_from_second(second);

    ss << std::setw(3) << std::setiosflags(std::ios::left) << std::setfill('0')
       << str.substr(dot + 1, std::min(str.size() - dot - 1, 3UL));
    ss >> this->milli_second;
}
