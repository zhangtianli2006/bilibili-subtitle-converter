#include <iostream>

#include "../include/subtitle.h"

int main(int argc, char** argv)
{
    sub::srt test;
    test.import_from_file("./test.srt");
    
    test.export_to_file("./test1.srt");
    return 0;
}