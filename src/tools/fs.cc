#include <fstream>
#include <string>

#include "../../include/tools/fs.h"

std::string tools::file_to_string(std::string file_path)
{
    std::ifstream f_in(file_path);

    std::string res;
    std::string temp;

    while (std::getline(f_in, temp))
        res += temp + "\n";

    return res;
}

void tools::string_to_file(std::string str, std::string file_path)
{
    std::ofstream f_out(file_path);
    f_out << str;
}
