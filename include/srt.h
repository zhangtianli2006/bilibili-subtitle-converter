#ifndef SRT_H
#define SRT_H

#include <vector>
#include <string>

#include "./tools/tools.h"

namespace sub
{
class srt_content
{
public:
    size_t id;
    tools::time_stamp start_time;
    tools::time_stamp end_time;

    std::string content;
};

class srt
{
public:
    void import_from_file(std::string path);
    void import_from_string(std::string str);

    std::string export_to_string();
    void export_to_file(std::string path);

    std::vector<srt_content> content;
};
} // namespace sub

#endif