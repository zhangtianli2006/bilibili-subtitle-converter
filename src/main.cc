#include <algorithm>
#include <args.hxx>
#include <cstring>
#include <iostream>
#include <string>

#include "../include/subtitle.h"
#include "../include/converter.h"

int main(int argc, char **argv)
{
    #ifdef __WIN32
    #elif __linux
    #endif

    args::ArgumentParser parser("CC subtitle converter Tianli Zhang (2020)");
    args::HelpFlag help(parser, "help", "Display this help menu", {'h', "help"});

    args::Group commands(parser, "Commands:");
    args::Command convert(commands, "convert", "convert format to format");

    args::Group subtitle_format(parser, "Subtitle formats:", args::Group::Validators::DontCare, args::Options::Global);
    args::Flag bts(subtitle_format, "bcc to srt", "bilibili format to srt format", {'b', "bts"});
    args::Flag stb(subtitle_format, "srt to bcc", "srt format to bilibili format", {'s', "stb"});
    args::Positional<std::string> path1(subtitle_format, "path1", "first file path");
    args::Positional<std::string> path2(subtitle_format, "path2", "second file path");

    try
    {
        parser.ParseCLI(argc, argv);
        if (convert)
        {
            if (bts and stb)
                throw args::UsageError("flag --bts and --stb should not be used together");

            if (bts)
                cvt::convert_bcc_to_srt_file(path1.Get(), path2.Get());
            if (stb)
                cvt::convert_srt_to_bcc_file(path1.Get(), path2.Get());
        }
    }
    catch (const args::Help &)
    {
        std::cout << parser;
        return 0;
    }
    catch (const args::ParseError &err)
    {
        std::cerr << "ERR: " << err.what() << std::endl;
        std::cerr << parser;
        return 1;
    }
    catch (const args::UsageError &err)
    {
        std::cerr << "ERR: " << err.what() << std::endl;
        return 1;
    }
    catch (const args::ValidationError &err)
    {
        std::cerr << "ERR: " << err.what() << std::endl;
        return 1;
    }

    return 0;
}