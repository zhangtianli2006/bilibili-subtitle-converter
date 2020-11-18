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
    root["font_size"] = this->font_size;
    root["font_color"] = this->font_color;
    root["background_alpha"] = this->background_alpha;
    root["background_color"] = this->background_color;
    root["Stroke"] = this->stroke;

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

void sub::bcc::export_to_file(std::string path)
{
    tools::string_to_file(this->export_to_string(), path);
}
