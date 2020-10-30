#include <iostream>

#include "../include/subtitle.h"
#include "../include/converter.h"

int main(int argc, char** argv)
{
    cvt::convert_srt_to_bcc_file("./test.srt", "./test.bcc");
    return 0;
}