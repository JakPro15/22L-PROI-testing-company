#include "../testingrecord.h"
#include "../../exceptions.h"
#include <cstdlib>
#include <cmath>
#include <algorithm>


void TestingRecord::checkId() const
{
    if(id < minId or id > maxId)
    {
        throw InvalidId("TestingRecord", id);
    }
}


TestingRecord::TestingRecord(int id, const AbstractGame &game, unsigned int maxTestersAmount): id(id), game(game), testers(),
    beingTested(false), testingFinished(false), realTestingTime(0), maxTestersAmount(maxTestersAmount)
{
    checkId();
    double timeChangeFactor = (double(std::rand()) / RAND_MAX) + 0.5;  // Will be between 0.5 and 1.5
    realTestingEffort = ceil(timeChangeFactor * game.getTestingTime()) * 5 * getMinTestersAmount();
    effortLeft = realTestingEffort;
    if(maxTestersAmount == 0)
    {
        this->maxTestersAmount = 2 * getMinTestersAmount();
    }
    else if(maxTestersAmount < getMinTestersAmount())
    {
        throw InvalidTestersAmount();
    }
}


const std::list<std::shared_ptr<Tester>>& TestingRecord::getTesters() const noexcept
{
    return testers;
}


void TestingRecord::addTester(std::shared_ptr<Tester> tester)
{
    if(testingFinished)
    {
        throw TestingEndedError();
    }
    else
    {
        if(testers.size() < getMaxTestersAmount())
        {
            if(std::find(testers.begin(), testers.end(), tester) == testers.end())
            {
                testers.push_back(tester);
                tester->setBusy(true);
                tester->setTestedGameRecord(this);
                if(testers.size() >= getMinTestersAmount())
                {
                    beingTested = true;
                }
            }
        }
    }
}


void TestingRecord::removeTester(std::shared_ptr<Tester> tester)
{
    if(testingFinished)
    {
        throw TestingEndedError();
    }
    else
    {
        auto testerIterator = std::find(testers.begin(), testers.end(), tester);
        if(testerIterator != testers.end())
        {
            tester->setBusy(false);
            tester->setTestedGameRecord(nullptr);
            testers.erase(testerIterator);
            if(testers.size() < getMinTestersAmount())
            {
                beingTested = false;
            }
        }
    }
}


int TestingRecord::getId() const noexcept
{
    return id;
}


bool TestingRecord::getBeingTested() const noexcept
{
    return beingTested;
}


const AbstractGame& TestingRecord::getGame() const noexcept
{
    return game;
}


unsigned int TestingRecord::getMinTestersAmount() const noexcept
{
    return game.getMinTestersAmount();
}


void TestingRecord::setMaxTestersAmount(unsigned int maxTestersAmount)
{
    if(testingFinished)
    {
        throw TestingEndedError();
    }
    else if(maxTestersAmount < getMinTestersAmount())
    {
        throw InvalidTestersAmount();
    }
    else
    {
        this->maxTestersAmount = maxTestersAmount;
    }
}


unsigned int TestingRecord::getMaxTestersAmount() const noexcept
{
    return maxTestersAmount;
}


void TestingRecord::advanceTesting(unsigned int effortPut)
{
    if(testingFinished)
    {
        throw TestingEndedError();
    }
    else if(beingTested)
    {
        if(effortLeft > effortPut)
        {
            effortLeft -= effortPut;
        }
        else
        {
            effortLeft = 0;
        }
    }
}


bool TestingRecord::checkFinished()
{
    if(testingFinished)
    {
        throw TestingEndedError();
    }
    else
    {
        // Done once per hour - can be used to increment the clock
        realTestingTime += 1;

        if(effortLeft == 0)
        {
            while(testers.size() > 0)
            {
                removeTester(*testers.begin());
            }
            testingFinished = true;
            return true;
        }
        else
        {
            return false;
        }
    }
}


int TestingRecord::getRealTime() const
{
    if(not testingFinished)
    {
        throw TestingNotEndedError();
    }
    else
    {
        return realTestingTime;
    }
}


Price TestingRecord::getRealPrice() const
{
    if(not testingFinished)
    {
        throw TestingNotEndedError();
    }
    else
    {
        Price realPrice = game.getTestingPrice();
        double effortRatio = double(realTestingEffort) / (game.getTestingTime() * 5 * getMinTestersAmount());
        realPrice *= effortRatio;
        // 20% discount if time much longer than expected
        if(getRealTime() > 1.5 * game.getTestingTime())
        {
            realPrice *= 0.8;
        }
        return realPrice;
    }
}


std::ostream& operator<<(std::ostream &stream, const TestingRecord &record) noexcept
{
    stream << "TestingRecord " << record.id - record.minId + 1;
    return stream;
}
