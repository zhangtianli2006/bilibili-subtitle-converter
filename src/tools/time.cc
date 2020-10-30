#include <algorithm>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

#include <iostream>

#include "../../include/tools/tools.h"

void tools::time_stamp::parse_from_second(double second)
{
    int int_second = second;
    double decimal_second = second - int_second;

    this->second = int_second % 60;
    int_second /= 60;

    this->minute = int_second % 60;
    int_second /= 60;

    this->hour = int_second % 60;
    int_second /= 60;

    this->milli_second = decimal_second * 1000;
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

double tools::time_stamp::export_to_second()
{
    std::string res_str;

    int second = this->hour * 60 * 60 + this->minute * 60 + this->second;
    res_str += std::to_string(second);

    res_str += ".";

    res_str += std::to_string(this->milli_second).substr(0, std::min(std::to_string(this->milli_second).size(), 3UL));

    std::stringstream ss;
    ss << res_str;
    double res;
    ss >> res;

    return res;
}

std::string tools::time_stamp::export_to_colon_time()
{
    std::string res;
    std::string temp_str;

    std::stringstream ss;
    ss << std::setw(2) << std::setiosflags(std::ios::right) << std::setfill('0') << this->hour;
    ss >> temp_str;
    res += temp_str + ":";
    ss.clear();

    ss << std::setw(2) << std::setiosflags(std::ios::right) << std::setfill('0') << this->minute;
    ss >> temp_str;
    res += temp_str + ":";
    ss.clear();

    ss << std::setw(2) << std::setiosflags(std::ios::right) << std::setfill('0') << this->second;
    ss >> temp_str;
    res += temp_str + ".";
    ss.clear();

    ss << std::setw(3) << std::setiosflags(std::ios::right) << std::setfill('0') << this->milli_second;
    ss >> temp_str;
    res += temp_str;

    return res;
}
