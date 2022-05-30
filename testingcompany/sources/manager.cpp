#include <chrono>
#include <random>
#include "../manager.h"
#include "../testingcompany.h"
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

Manager::Manager(int id, std::string name, std::string surname, TestingCompany& company):
    Worker('a', id, name, surname, company)
{
    checkId();
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator (seed);
    productivity = (generator() % 8) + 2;  
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

void Manager::doWork() noexcept
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