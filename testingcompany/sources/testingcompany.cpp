#include "../testingcompany.h"
#include "../../exceptions.h"
#include "../../games/abstractgame.h"
#include "../../testingcompany/tester.h"
#include "../../testingcompany/manager.h"
#include "../../simulation/outputhandler.h"
#include <vector>

TestingCompany::TestingCompany(OutputHandler& out,
    std::vector<std::shared_ptr<AbstractWorker>> workers,
    std::vector<std::shared_ptr<Tester>> testers):
    effort(0), currentRequestId(11000001), database(out, 7000001, *this),
    records{}, workers{workers}, testers{testers}, out(out)
{}

int TestingCompany::getRequestId()
{
    return currentRequestId++;
}

unsigned int TestingCompany::getEffort() const noexcept
{
    return effort;
}

int TestingCompany::getRecords() const noexcept
{
    return records.size();
}

int TestingCompany::getWorkers() const noexcept
{
    return workers.size();
}

int TestingCompany::getTesters() const noexcept
{
    return testers.size();
}

std::vector<TestingCompany::Record> TestingCompany::showRecords() const noexcept
{
    std::vector<TestingCompany::Record> recordsCopy = records;
    return recordsCopy;
}

void TestingCompany::addEffort(unsigned int effort) noexcept
{
    this->effort += effort;
}

void TestingCompany::addTester(std::shared_ptr<Tester> tester)
{
    testers.push_back(tester);
    workers.push_back(tester);
}

void TestingCompany::addManager(std::shared_ptr<Manager> manager)
{
    workers.push_back(manager);
}

void TestingCompany::testingFinished(const AbstractGame &game)
{
    TestingCompany::Record newRecord {game, false, 0, true};
    records.push_back(newRecord);
    out << "Finished testing of: " << game << " payment pending."<< OutputHandler::endlWait;
}

void TestingCompany::paymentDone(const AbstractGame& game)
{
    for(auto& record: records)
    {
        if(record.testedGame == game)
        {
            record.paid = true;
            if(record.delay > 40)
            {
                record.onTime = false;
            }
            out << "Confirmed payment of: " << game << OutputHandler::endlWait;
        }
    }
}

void TestingCompany::obtainTestingRequest(const AbstractGame &game)
{
    database.newTestingRequest(game);
    out << "Received testing request for: " << game << OutputHandler::endlWait;
}

void TestingCompany::advanceTime()
{
    for(std::shared_ptr<AbstractWorker> worker: workers)
    {
        worker->doWork();
    }
    database.checkRecords();
    for(TestingCompany::Record record: records)
    {
        if(record.paid == false)
        {
            record.delay++;
        }
    }
    for(std::shared_ptr<Tester> tester: testers)
    {
        if(tester->getBusy() == false)
        {
            database.assignTester(tester);
        }
    }
    if(database.getTestRequestsAmount() > 0)
    {
        database.advanceRequestHandling(effort);
    }
    effort = 0;
}

bool TestingCompany::operator==(const TestingCompany& company) const noexcept
{
    return this == &company;
}

bool TestingCompany::operator!=(const TestingCompany& company) const noexcept
{
    return !(*this == company);
}

std::ostream& operator<<(std::ostream& os, const TestingCompany& company) noexcept
{
    os << "Testing Company";
    return os;
}