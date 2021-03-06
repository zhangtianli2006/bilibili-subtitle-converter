#ifndef TOOLS_FS_H
#define TOOLS_FS_H

#include <string>

namespace tools
{
std::string file_to_string(std::string file_path);
void string_to_file(std::string str, std::string file_path);
} // namespace tools

#endif