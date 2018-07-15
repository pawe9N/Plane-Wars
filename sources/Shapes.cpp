#include "../headers/Shapes.h"

//get shapes from txt file
std::string Shapes::getFileContents (std::ifstream& File)
{
    std::string Lines = "";

    try
    {
        while (File.good ())
        {
            std::string TempLine;
            std::getline (File , TempLine);

            Lines += TempLine;
        }
        return Lines;
    }
    catch(std::ifstream::failure e)
    {
        return "ERROR related with reading file!";
    }
}
