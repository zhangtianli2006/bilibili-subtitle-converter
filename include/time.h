#ifndef TIME_H
#define TIME_H

#include <string>

namespace tool
{
class time_stamp
{
public:
    unsigned short hour;
    unsigned short minute;
    unsigned short second;
    unsigned short milli_second;

    void init(unsigned short h, unsigned short m, unsigned short s, unsigned short ms);
    void parse_from_srt(std::string str);
};
} // namespace tool

#endif