#include "../manager.h"
#include "../../exceptions.h"

void Manager::checkId() const
{
    if(id < minId or id > maxId)
    {
        throw InvalidId("Manager", id);
    }
}

std::string Manager::getUniqueName() const noexcept
{
    return "Manager " + std::to_string(id - minId + 1);
}

Manager::Manager(int id, std::string name, std::string surname, unsigned int productivity, TestingCompany& company):
    Worker('a', id, name, surname), productivity(productivity), company(company)
{
    checkId();
    if ((1 <= productivity) && (productivity <= 9))
    {
        this->productivity = productivity;
    }
    else
    {
        throw ProductivityOutOfRangeException();
    }
}

Manager::~Manager(){}

bool Manager::operator==(const Manager& manager) const noexcept
{
    if (id == manager.getId())
    {
        return true;
    }
    else
    {
        return false;
    }
}

unsigned int Manager::getProductivity() const noexcept
{
    return productivity;
}

void Manager::produceEffort()
{
    company.addEffort(productivity);
}

bool Manager::operator!=(const Manager& manager) const noexcept
{
    return !(*this == manager);
}

std::ostream& operator<<(std::ostream& os, const Manager &manager) noexcept
{
    os << manager.getUniqueName();
    return os;
}