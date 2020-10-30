#include <fstream>
#include <istream>
#include <sstream>
#include <vector>

#include "../include/srt.h"
#include "../include/time.h"

void sub::srt::import_from_file(std::string path)
{
    std::ifstream f_in(path);

    std::string res_str;
    std::string temp_str;

    while (std::getline(f_in, temp_str))
        res_str += temp_str + "\n";

    this->import_from_string(res_str);
}

void sub::srt::import_from_string(std::string str)
{
    std::stringstream ss;
    ss << str;

    size_t id;
    while (ss >> id)
    {
        sub::srt_content temp_content;

        temp_content.id = id;

        std::string start_time_str;
        std::string end_time_str;
        std::string arrow;
        ss >> start_time_str >> arrow >> end_time_str;

        temp_content.start_time.parse_from_srt_time(start_time_str);
        temp_content.end_time.parse_from_srt_time(end_time_str);

        std::string temp_str;
        while (std::getline(ss, temp_str))
        {
            if (temp_str.empty())
                break;

            temp_content.content += temp_str + "\n";
        }

        this->content.push_back(temp_content);
    }
}
