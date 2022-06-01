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

OutputHandler& OutputHandler::operator<<(OutputHandler& (*func)(OutputHandler&))
{
    return func(*this);
}

OutputHandler& OutputHandler::endlWait(OutputHandler& out)
{
    if(debug)
    {
    out << '\n';
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    return out;
}