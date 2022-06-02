#include "../testingcompany.h"
#include "../../exceptions.h"
#include "../../games/abstractgame.h"
#include "../tester.h"
#include "../manager.h"
#include "../../producer/producer.h"
#include "../../simulation/outputhandler.h"
#include <vector>


void TestingCompany::Record::checkId() const
{
    if(id < minId or id > maxId)
    {
        throw InvalidId("TestingCompany::Record", id);
    }
}

TestingCompany::Record::Record(int id, const AbstractGame& testedGame, Price price):
    id(id), testedGame(testedGame), testingPrice(price), paid(false), delay(0), onTime(true)
{
    checkId();
}

void TestingCompany::checkId() const
{
    if(id < minId or id > maxId)
    {
        throw InvalidId("TestingCompany", id);
    }
}

TestingCompany::TestingCompany(int id, OutputHandler& out,
    std::vector<std::shared_ptr<AbstractWorker>> workers,
    std::vector<std::shared_ptr<Tester>> testers):
    id(id), effort(0), currentRequestId(11000001), currentRecordId(16000001),
    database(out, id - minId + TestingDatabase::minId, *this), records{}, workers{workers},
    testers{testers}, out(out)
{
    checkId();
}

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

const std::vector<TestingCompany::Record>& TestingCompany::showRecords() const noexcept
{
    const std::vector<TestingCompany::Record>& recordsCopy = records;
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

void TestingCompany::testingFinished(const AbstractGame& game, Price price)
{
    TestingCompany::Record newRecord(currentRecordId++, game, price);
    records.push_back(newRecord);
    game.producer.testingFinished(game, price);
    out << "Finished testing of: " << game << ", payment pending."<< OutputHandler::endlWait;
}

void TestingCompany::paymentDone(const AbstractGame& game)
{
    for(auto& record: records)
    {
        if(record.testedGame == game)
        {
            record.paid = true;
            out << "Confirmed payment for testing of: " << game;
            if(record.delay > 40)
            {
                record.onTime = false;
                out << " past due date";
            }
            out << OutputHandler::endlWait;
        }
    }
}

void TestingCompany::obtainTestingRequest(const AbstractGame& game)
{
    out << "Received testing request for: " << game << OutputHandler::endlWait;
    database.newTestingRequest(game);
}

void TestingCompany::advanceTime()
{
    for(std::shared_ptr<AbstractWorker> worker: workers)
    {
        worker->doWork();
    }
    database.checkRecords();
    for(TestingCompany::Record& record: records)
    {
        if(record.paid == false)
        {
            record.delay++;
        }
    }
    for(std::shared_ptr<Tester> tester: testers)
    {
        if(effort >= 4)
        {
            if(tester->getBusy() == false)
            {
                effort -= 4;
                if(!database.assignTester(tester))
                {
                    break;
                }
            }
        }
        else
        {
            break;
        }
    }
    if(database.getTestRequestsAmount() > 0)
    {
        database.advanceRequestHandling(effort);
    }
    effort = 0;
}

bool TestingCompany::isThereWork() const noexcept
{
    if(database.getTestRequestsAmount() > 0)
    {
        return true;
    }
    else
    {
        for(std::shared_ptr<Tester> testerPtr: testers)
        {
            if(!testerPtr->getBusy())
            {
                return true;
            }
        }
        return false;
    }
}

bool TestingCompany::operator==(const TestingCompany& company) const noexcept
{
    if (id == company.id)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool TestingCompany::operator!=(const TestingCompany& company) const noexcept
{
    return !(*this == company);
}

std::ostream& operator<<(std::ostream& os, const TestingCompany& company) noexcept
{
    os << "TestingCompany " << company.id - company.minId + 1;
    return os;
}