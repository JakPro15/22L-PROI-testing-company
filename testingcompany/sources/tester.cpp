#include <chrono>
#include <random>
#include "../tester.h"
#include "../../exceptions.h"
#include "../../simulation/outputhandler.h"


void Tester::checkId() const
{
    if(id < minId or id > maxId)
    {
        throw InvalidId("Tester", id);
    }
}

std::string Tester::getUniqueName() const noexcept
{
    return "Tester " + std::to_string(id - minId + 1);
}

Tester::Tester(int id, std::string name, std::string surname, TestingCompany& company, OutputHandler& out):
    Worker('a', id, name, surname, company, out), busyness(false), gameRecord(nullptr)
{
    checkId();
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator (seed);
    productivity = (generator() % 8) + 2;
}

Tester::~Tester(){}

unsigned int Tester::getProductivity() const noexcept
{
    return productivity;
}

void Tester::setBusy(bool bus)
{
    busyness = bus;
}

bool Tester::getBusy() const noexcept
{
    return busyness;
}

void Tester::setTestedGameRecord(TestingRecord* record)
{
    gameRecord = record;
}

TestingRecord* Tester::getTestedGameRecord() const noexcept
{
    return gameRecord;
}

void Tester::doWork() noexcept
{
    if(gameRecord)
    {
        gameRecord->advanceTesting(productivity);
        out << *this << "has done their work." << OutputHandler::endlWait;
    }
}

bool Tester::operator==(const Tester& tester) const noexcept
{
    if (id == tester.getId())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Tester::operator!=(const Tester& tester) const noexcept
{
    return !(*this == tester);
}

std::ostream& operator<<(std::ostream& os, const Tester &tester) noexcept
{
    os << tester.getUniqueName();
    return os;
}