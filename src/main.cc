#include <iostream>

#include "../include/bcc.h"

int main(int argc, char** argv)
{
    sub::bcc test;
    test.import_from_file("./test.json");
    
    test.export_to_file("./test1.json");
    return 0;
}