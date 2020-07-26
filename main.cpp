#include <string>
#include <vector>
#include <iostream>
#include <Console/IO.hpp>
#include <PhilosophersProblem/DiningTable.hpp>


int main(int argc, char* argv[])
{
    IO io;

    // input argument define number of rows
    if(io.validateArgs((uint32_t)argc, argv))
    {
        DiningTable diningTable(io.getInputArgValue());
        diningTable.startDinner();
    }
    else
    {
        std::cout << "Invalid arguments!" << std::endl;
        std::cout << "Program accepts unsigned integer as number of required philosphers." << std::endl;
    }

    return 0;
}
