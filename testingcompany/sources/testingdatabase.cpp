#include "../testingdatabase.h"
#include "../testingrecord.h"
#include "../testingcompany.h"
#include "../tester.h"
#include "../../exceptions.h"
#include "../../games/abstractgame.h"
#include "../../simulation/outputhandler.h"
#include <sstream>


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


TestingDatabase::Request::Request(int id, const AbstractGame &game): id(id), game(game)
{
    checkId();
    effortLeft = effortPerRequest;
}


std::string TestingDatabase::Request::getUniqueName() const noexcept
{
    return "TestingDatabase::Request " + std::to_string(id - minId + 1);
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


TestingDatabase::TestingDatabase(OutputHandler &out, int id, TestingCompany &company): out(out), testingRequests(), gamesNotBeingTested(),
    gamesBeingTested(), id(id), company(company)
{
    checkId();
}


void TestingDatabase::newTestingRequest(const AbstractGame &game)
{
    Request newRequest(company.getRequestId(), game);
    std::stringstream stringstr;
    stringstr << *this << " encloses " << game << " in " << newRequest.getUniqueName();
    out << stringstr.str();
    testingRequests.push(newRequest);
}


void TestingDatabase::advanceRequestHandling(unsigned int effortPut) noexcept
{
    Request &topRequest = testingRequests.front();
    if(topRequest.effortLeft > effortPut)
    {
        topRequest.effortLeft -= effortPut;
        std::stringstream stringstr;
        stringstr << *this << " advances " << topRequest.getUniqueName() << " by " << effortPut;
        out << stringstr.str();
    }
    else
    {
        // Request processed - delete it and create a Testing Record from it.
        // Request IDs are always bigger by 5000000 than TestingRecord ids, and this is the only place where
        // TestingRecords are created - database doesn't need to ask the company for a new ID for the record.
        gamesNotBeingTested.push_back(std::make_unique<TestingRecord>(out, topRequest.id - 5000000, topRequest.game));
        std::stringstream stringstr;
        stringstr << *this << " finishes " << topRequest.getUniqueName() << "'s processing"
                  << " and creates " << *(gamesNotBeingTested.back()) << " to enclose " << topRequest.game;
        out << stringstr.str();
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
            company.testingFinished(record.game);
            std::stringstream stringstr;
            stringstr << *this << " notices " << (*iterator)->game << "'s testing has finished";
            out << stringstr.str();
            recordsToRemove.push(iterator);
        }
        else if(not record.getBeingTested())
        {
            // If testers stopped testing an unfinished game, move it back to the beginning of the queue.
            std::stringstream stringstr;
            stringstr << *this << " notices " << (*iterator)->game << "'s testing has paused";
            out << stringstr.str();
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
        std::stringstream stringstr;
        stringstr << *this << " assigns " << *testerPtr << " to " << gamesNotBeingTested.front()->game;
        out << stringstr.str();
        if(gamesNotBeingTested.front()->getBeingTested())
        {
            std::stringstream stringstr;
            stringstr << *this << " notices " << gamesNotBeingTested.front()->game << "'s testing has begun";
            out << stringstr.str();
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
                std::stringstream stringstr;
                stringstr << *this << " assigns " << *testerPtr << " to " << recordPtr->game;
                out << stringstr.str();
                return true;
            }
        }
    }
    std::stringstream stringstr;
    stringstr << *this << " fails to assign " << *testerPtr << " to a game";
    out << stringstr.str();
    return false;
}


std::ostream& operator<<(std::ostream &stream, const TestingDatabase &database) noexcept
{
    stream << "TestingDatabase " << database.id - database.minId + 1;
    return stream;
}
