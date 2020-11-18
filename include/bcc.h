#ifndef BCC_H
#define BCC_H

#include <vector>
#include <string>

#include "./tools/tools.h"

namespace sub
{
class bcc_content
{
public:
    tools::time_stamp from;
    tools::time_stamp to;
    unsigned int location;

    std::string content;
};

class bcc
{
public:
    void import_from_string(std::string str);
    void import_from_file(std::string path);

    std::string export_to_string();
    void export_to_file(std::string path);

    std::vector<bcc_content> body;
};

} // namespace sub

#endif