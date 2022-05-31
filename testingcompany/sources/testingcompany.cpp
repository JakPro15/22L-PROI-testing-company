#include "../testingcompany.h"
#include "../../exceptions.h"
#include "../../games/abstractgame.h"
#include "../../testingcompany/tester.h"
#include "../../testingcompany/manager.h"
#include <vector>

TestingCompany::TestingCompany(OutputHandler& out,
    std::vector<std::shared_ptr<AbstractWorker>> workers,
    std::vector<std::shared_ptr<Tester>> testers):
    effort(0), currentRequestId(11000001), database(out, 7000001, *this),
    records{}, workers{workers}, testers{testers}, out(out)
{}

int TestingCompany::getRequestId()
{
    int returnId  = currentRequestId++;
    if (returnId > 11999999)
    {
        return returnId;
    }
    else
    {
        throw InvalidId("request", returnId);
    }
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
}

void TestingCompany::paymentDone(const AbstractGame& game)
{
    for(auto record: records)
    {
        if(record.testedGame == game)
        {
            record.paid = true;
            if(record.delay > 40)
            {
                record.onTime = false;
            }
        }
    }
}

void TestingCompany::obtainTestingRequest(const AbstractGame &game)
{
    database.newTestingRequest(game);
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
    database.advanceRequestHandling(effort);
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