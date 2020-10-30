#include <json/json.h>
#include <fstream>
#include <string>
#include <vector>

#include "../include/tools/tools.h"
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
    this->import_from_string(tools::file_to_string(path));
}