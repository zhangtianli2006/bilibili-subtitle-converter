#include <json/json.h>
#include <fstream>
#include <string>
#include <vector>

#include "../include/tools/time.h"
#include "../include/bcc.h"

void sub::bcc::import_from_string(std::string str)
{
    std::stringstream ss;
    ss << str;

    Json::Value root;
    ss >> root;

    this->font_size = root["font_size"].asFloat();
    this->font_color = root["font_color"].asString();
    this->background_alpha = root["background_alpha"].asFloat();
    this->background_color = root["background_color"].asString();
    this->stroke = root["Stroke"].asString();

    for (int i = 0; i < root["body"].size(); i++)
    {
        sub::bcc_content temp_content;

        std::string from_str = root["body"][i]["from"].asString();
        std::string to_str = root["body"][i]["to"].asString();
        temp_content.from.parse_from_bcc_time(from_str);
        temp_content.from.parse_from_bcc_time(to_str);

        temp_content.location = root["body"][i]["location"].asInt();

        temp_content.content = root["body"][i]["content"].asString();

        this->body.push_back(temp_content);
    }
}

void sub::bcc::import_from_file(std::string path)
{
    std::ifstream f_in(path);

    std::string res_str;
    std::string temp_str;

    while (std::getline(f_in, temp_str))
        res_str += temp_str + "\n";

    this->import_from_string(res_str);
}