#include <iostream>
#include <dbg.h>

#include "../include/bcc.h"

int main(int argc, char** argv)
{
    sub::bcc test;
    test.import_from_file("./test.json");
    
    for (auto i : test.body)
        std::cout << i.content << "\n";
    return 0;
}