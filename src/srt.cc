#include <fstream>
#include <istream>
#include <sstream>
#include <vector>

#include "../include/srt.h"
#include "../include/tools/tools.h"

void sub::srt::import_from_file(std::string path) { this->import_from_string(tools::file_to_string(path)); }

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

        ss.get();

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

std::string sub::srt::export_to_string()
{
    std::string res;

    for (auto i : this->content)
    {
        res += std::to_string(i.id) + "\n";
        res += i.start_time.export_to_colon_time() + " --> " + i.end_time.export_to_colon_time() + "\n";
        res += i.content + "\n\n";
    }
    
    return res;
}

void sub::srt::export_to_file(std::string path)
{
    tools::string_to_file(this->export_to_string(), path);
}
