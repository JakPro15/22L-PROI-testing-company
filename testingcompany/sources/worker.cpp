#include "../worker.h"
#include "../../exceptions.h"
#include "../checkallwhitespace.h"

void Worker::checkId() const
{
    if(id < minId or id > maxId)
    {
        throw InvalidId("Worker", id);
    }
}

std::string Worker::getUniqueName() const noexcept
{
    return "Worker " + std::to_string(id - minId + 1);
}

Worker::Worker(char, int id, std::string name, std::string surname):
    AbstractWorker(id), name(name), surname(surname)
{
    if (checkAllWhitespace(name))
    {
        throw EmptyNameException();
    }
    if (checkAllWhitespace(surname))
    {
        throw EmptyNameException("Surname");
    }   
}

Worker::Worker(int id, std::string name, std::string surname):
    Worker('a', id, name, surname)
{
    checkId();
}

Worker::~Worker(){}

int Worker::getId() const noexcept
{
    return id;
}

void Worker::setName(std::string name)
{
    if (checkAllWhitespace(name))
    {
        throw EmptyNameException();
    }
    else
    {
        this->name = name;
    }
}

std::string Worker::getName() const noexcept
{
    return name;
}

void Worker::setSurname(std::string surname)
{
    if (checkAllWhitespace(surname))
    {
        throw EmptyNameException("Surname");
    }
    else
    {
        this->surname = surname;
    }
}

std::string Worker::getSurname() const noexcept
{
    return surname;
}

bool Worker::operator==(const AbstractWorker& worker) const noexcept
{
    if(id == worker.getId())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Worker::operator!=(const AbstractWorker& worker) const noexcept
{
    return !(*this == worker);
}


std::ostream& operator<<(std::ostream& os, const Worker &worker) noexcept
{
    os << worker.getUniqueName();
    return os;
}

