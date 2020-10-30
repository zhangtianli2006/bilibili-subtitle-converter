#include <sstream>
#include <sstream>
#include <string>
#include <vector>

#include "../include/time.h"

void tool::time_stamp::init(unsigned short h, unsigned short m, unsigned short s, unsigned short ms)
{
    this->hour = h;
    this->minute = m;
    this->second = s;
    this->milli_second = ms;
}

void tool::time_stamp::parse_from_srt(std::string str)
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
