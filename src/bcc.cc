#include <json/json.h>
#ifdef __WIN32
#include <filesystem>
#endif
#include <fstream>
#include <string>
#include <vector>

#include "../include/tools/tools.h"
#include "../include/bcc.h"

sub::bcc_config::bcc_config()
{
    std::string config_path;
#ifdef __WIN32
    config_path = "";
    auto path = std::filesystem::temp_directory_path().parent_path().parent_path();
    path /= "Roaming";

    if (!std::filesystem::exists(path))
        std::filesystem::create_directories(path);

    config_path = path;
#elif __linux
    config_path = "~/.sub_cvt/bcc_config.json";
#endif

    std::ifstream f_in(config_path);
    Json::Value root;
    f_in >> root;

    this->font_size = root["font_size"].asFloat();
    this->font_color = root["font_color"].asString();
    this->background_alpha = root["background_alpha"].asFloat();
    this->background_color = root["background_color"].asString();
    this->stroke = root["Stroke"].asString();
}

void sub::bcc::import_from_string(std::string str)
{
    std::stringstream ss;
    ss << str;

    Json::Value root;
    ss >> root;

    this->config.font_size = root["font_size"].asFloat();
    this->config.font_color = root["font_color"].asString();
    this->config.background_alpha = root["background_alpha"].asFloat();
    this->config.background_color = root["background_color"].asString();
    this->config.stroke = root["Stroke"].asString();

    for (int i = 0; i < root["body"].size(); i++)
    {
        sub::bcc_content temp_content;

        double from = root["body"][i]["from"].asDouble();
        double to = root["body"][i]["to"].asDouble();
        temp_content.from.parse_from_second(from);
        temp_content.to.parse_from_second(to);

        temp_content.location = root["body"][i]["location"].asInt();

        temp_content.content = root["body"][i]["content"].asString();

        this->body.push_back(temp_content);
    }
}

void sub::bcc::import_from_file(std::string path) { this->import_from_string(tools::file_to_string(path)); }

std::string sub::bcc::export_to_string()
{
    Json::Value root;
    root["font_size"] = this->config.font_size;
    root["font_color"] = this->config.font_color;
    root["background_alpha"] = this->config.background_alpha;
    root["background_color"] = this->config.background_color;
    root["Stroke"] = this->config.stroke;

    for (int i = 0; i < this->body.size(); i++)
    {
        root["body"][i]["from"] = this->body[i].from.export_to_second();
        root["body"][i]["to"] = this->body[i].to.export_to_second();
        root["body"][i]["location"] = this->body[i].location;
        root["body"][i]["content"] = this->body[i].content;
    }

    Json::Value conf = []() {
        Json::Value conf;
        Json::StreamWriterBuilder::setDefaults(&conf);
        conf["emitUTF8"] = true;

        return conf;
    }();

    std::ostringstream oss;
    Json::StreamWriterBuilder s_builder;
    s_builder.settings_ = conf;

    std::unique_ptr<Json::StreamWriter> writer(s_builder.newStreamWriter());
    writer->write(root, &oss);

    return oss.str();
}

void sub::bcc::export_to_file(std::string path) { tools::string_to_file(this->export_to_string(), path); }
