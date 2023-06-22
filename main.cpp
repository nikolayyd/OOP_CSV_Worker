#include <iostream>
#include <string>

#include "headers/Program.h"

int main(int argc, char const *argv[])
{
    try
    {
        Program csvWorker;
        csvWorker.startProgram();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}
