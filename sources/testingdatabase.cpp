#include "../testingdatabase.h"
#include "../exceptions.h"


void TestingDatabase::checkId() const
{
    if(id < minId or id > maxId)
    {
        throw InvalidId("TestingDatabase", id);
    }
}


void TestingDatabase::Request::checkId() const
{
    if(id < minId or id > maxId)
    {
        throw InvalidId("TestingDatabase::Request", id);
    }
}


TestingDatabase::Request::Request(int id, const Game &game): id(id), game(game)
{
    checkId();
    effortLeft = effortPerRequest;
}


TestingCompany& TestingDatabase::getCompany() const noexcept
{
    return company;
}


unsigned int TestingDatabase::getGamesBeingTestedAmount() const noexcept
{
    return gamesBeingTested.size();
}


unsigned int TestingDatabase::getGamesWaitingForTestersAmount() const noexcept
{
    return gamesNotBeingTested.size();
}


unsigned int TestingDatabase::getTestRequestsAmount() const noexcept
{
    return testingRequests.size();
}


TestingDatabase::TestingDatabase(int id, TestingCompany &company): id(id), company(company), testingRequests(),
    gamesNotBeingTested(), gamesBeingTested()
{
    checkId();
}


int TestingDatabase::getId() const noexcept
{
    return id;
}


void TestingDatabase::newTestingRequest(const Game &game)
{
    Request newRequest(company.getRequestId(), game);
    testingRequests.push(newRequest);
}


void TestingDatabase::advanceRequestHandling(unsigned int effortPut) noexcept
{
    Request &topRequest = testingRequests.front();
    if(topRequest.effortLeft > effortPut)
    {
        topRequest.effortLeft -= effortPut;
    }
    else
    {
        // Request processed - delete it and create a Testing Record from it.
        // Request IDs are always bigger by 5000000 than TestingRecord ids, and this is the only place where
        // TestingRecords are created - database doesn't need to ask the company for a new ID for the record.
        gamesNotBeingTested.push_back(std::make_unique<TestingRecord>(topRequest.id - 5000000, topRequest.game));
        testingRequests.pop();
    }
}


void TestingDatabase::checkRecords()
{
    for(std::unique_ptr<TestingRecord> &recordPtr: gamesNotBeingTested)
    {
        recordPtr->checkFinished();
    }
    std::queue<std::list<std::unique_ptr<TestingRecord>>::iterator> recordsToRemove;
    for(auto iterator = gamesBeingTested.begin(); iterator != gamesBeingTested.end(); iterator++)
    {
        TestingRecord &record = **iterator;
        if(record.checkFinished())
        {
            company.testingFinished(record.getGame());
            recordsToRemove.push(iterator);
        }
        else if(not record.getBeingTested())
        {
            // If testers stopped testing an unfinished game, move it back to the beginning of the queue.
            gamesNotBeingTested.push_front(std::move(*iterator));
            recordsToRemove.push(iterator);
        }
    }
    while(not recordsToRemove.empty())
    {
        auto iterator = recordsToRemove.front();
        gamesBeingTested.erase(iterator);
        recordsToRemove.pop();
    }
}


bool TestingDatabase::assignTester(std::shared_ptr<Tester> testerPtr)
{
    if(not gamesNotBeingTested.empty())
    {
        gamesNotBeingTested.front()->addTester(testerPtr);
        if(gamesNotBeingTested.front()->getBeingTested())
        {
            gamesBeingTested.push_back(std::move(gamesNotBeingTested.front()));
            gamesNotBeingTested.pop_front();
        }
        return true;
    }
    else
    {
        for (std::unique_ptr<TestingRecord> &recordPtr: gamesBeingTested)
        {
            if(recordPtr->getTesters().size() < recordPtr->getMaxTestersAmount())
            {
                recordPtr->addTester(testerPtr);
                return true;
            }
        }
    }
    return false;
}

