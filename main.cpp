#include <string>
#include <vector>
#include <iostream>
#include <Console/IO.hpp>
#include <Console/Graphics.hpp>


int main(int argc, char* argv[])
{
    IO io;

    // input argument define number of rows
    if(io.validateArgs((uint32_t)argc, argv))
    {
        std::vector<std::string> columnsNames{ "Column1", "Column2", "Column3", "Column4", "Column5" };
        std::vector<std::vector<std::string>> rows(io.getInputArgValue(), { "rowX", "rowX", "rowX", "rowX", "rowX" });

        Graphics graphics(columnsNames, rows);
        graphics.display();
    }
    else
    {
        std::cout << "Invalid arguments!" << std::endl;
        std::cout << "Program accepts unsigned integer as number of required philosphers." << std::endl;
    }

    return 0;
}
