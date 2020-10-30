#ifndef CONVERTER_H
#define CONVERTER_H

#include <string>

namespace cvt
{
void convert_bcc_to_srt_file(std::string bcc_file_path, std::string srt_file_path);
std::string convert_bcc_to_srt_string(std::string bcc_str);

void convert_srt_to_bcc_file(std::string srt_file_path, std::string bcc_file_path);
std::string convert_srt_to_bcc_string(std::string srt_str);
} // namespace cvt

#endif