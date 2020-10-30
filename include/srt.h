#ifndef SRT_H
#define SRT_H

#include <vector>
#include <string>

#include "./time.h"

namespace sub
{
class srt_content
{
public:
    size_t id;
    tool::time_stamp start_time;
    tool::time_stamp end_time;

    std::string content;
};

class srt
{
public:
    void import_from_file(std::string file_path);
    void import_from_string(std::string str);

private:
    std::vector<srt_content> content;
};
} // namespace sub

#endif