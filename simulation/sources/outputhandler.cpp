#include "../outputhandler.h"
#include "../../exceptions.h"


OutputHandler::OutputHandler(std::string fileName):
    outputStream(std::cout)
{
    file.open(fileName);
    if(!file)
    {
        throw FileError(fileName);
    }
}

OutputHandler::~OutputHandler()
{
    file.close();
}