#include "../outputhandler.h"
#include "../../exceptions.h"
#include <thread>
#include <chrono>

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

template<typename T>
OutputHandler& OutputHandler::operator<<(const T& object)
{
    file << object << std::endl;
    outputStream << object << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    return *this;
}