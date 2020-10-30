#ifndef TOOLS_TIME_H
#define TOOLS_TIME_H

#include <string>

namespace tools
{
class time_stamp
{
public:
    unsigned short hour;
    unsigned short minute;
    unsigned short second;
    unsigned short milli_second;

    void init(unsigned short h, unsigned short m, unsigned short s, unsigned short ms);

    void parse_from_second(int second);

    void parse_from_srt_time(std::string str);
    void parse_from_bcc_time(std::string str);

};
} // namespace tools

#endif