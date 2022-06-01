#include "../outputhandler.h"
#include "../../exceptions.h"
#include <thread>
#include <chrono>

void OutputHandler::checkId() const
{
    if(id < minId or id > maxId)
    {
        throw InvalidId("OutputHandler", id);
    }
}

OutputHandler::OutputHandler(int id, std::string fileName):
    id(id), outputStream(std::cout)
{
    checkId();

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