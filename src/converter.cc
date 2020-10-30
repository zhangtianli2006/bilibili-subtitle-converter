#include <string>

#include "../include/converter.h"
#include "../include/subtitle.h"
#include "../include/tools/tools.h"

void cvt::convert_bcc_to_srt_file(std::string bcc_file_path, std::string srt_file_path)
{
    tools::string_to_file(cvt::convert_bcc_to_srt_string(tools::file_to_string(bcc_file_path)), srt_file_path);
}

std::string cvt::convert_bcc_to_srt_string(std::string bcc_str)
{
    sub::bcc bcc_obj;
    sub::srt srt_obj;

    bcc_obj.import_from_string(bcc_str);

    for (size_t i = 0; i < bcc_obj.body.size(); i++)
    {
        sub::srt_content temp_content;
        temp_content.id = i + 1;

        temp_content.start_time = bcc_obj.body[i].from;
        temp_content.end_time = bcc_obj.body[i].to;

        temp_content.content = bcc_obj.body[i].content;

        srt_obj.content.push_back(temp_content);
    }

    return srt_obj.export_to_string();
}

void cvt::convert_srt_to_bcc_file(std::string srt_file_path, std::string bcc_file_path)
{
    tools::string_to_file(cvt::convert_srt_to_bcc_string(tools::file_to_string(srt_file_path)), bcc_file_path);
}

std::string cvt::convert_srt_to_bcc_string(std::string srt_str)
{
    sub::bcc bcc_obj;
    sub::srt srt_obj;

    srt_obj.import_from_string(srt_str);

    for (auto i : srt_obj.content)
    {
        sub::bcc_content temp_content;
        temp_content.from = i.start_time;
        temp_content.to = i.end_time;

        temp_content.content = i.content;

        bcc_obj.body.push_back(temp_content);
    }

    return bcc_obj.export_to_string();
}
