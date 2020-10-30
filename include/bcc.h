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

    float font_size;
    std::string font_color;
    float background_alpha;
    std::string background_color;
    std::string stroke;

    std::vector<bcc_content> body;
};

} // namespace sub

#endif