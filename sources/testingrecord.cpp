#include "testingrecord.h"
#include "exceptions.h"
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


void TestingRecord::finalizeTesting() noexcept
{
    beingTested = false;
    testingFinished = true;
    for(Tester &tester: testers)
    {
        tester.setBusy(false);
    }
    testers = std::list<Tester>();
}


TestingRecord::TestingRecord(int id, const Game &game, int maxTestersAmount): id(id), game(game), testers(), beingTested(false),
    testingFinished(false), realTestingTime(0), maxTestersAmount(maxTestersAmount)
{
    checkId();
    double timeChangeFactor = (double(std::rand()) / RAND_MAX) + 0.5;  // Will be between 0.5 and 1.5
    realTestingEffort = ceil(timeChangeFactor * game.getTestingTime());
    effortLeft = realTestingEffort;
    if(maxTestersAmount == -1)
    {
        maxTestersAmount = 2 * getMinTestersAmount();
    }
}


const std::list<Tester>& TestingRecord::getTesters() const noexcept
{
    return testers;
}


void TestingRecord::addTester(Tester &tester)
{
    if(std::find(testers.begin(), testers.end(), tester) == testers.end())
    {
        testers.push_back(tester);
    }
}


void TestingRecord::removeTester(const Tester &tester) noexcept
{
    testers.remove(tester);
}


int TestingRecord::getId() const noexcept
{
    return id;
}


const Game& TestingRecord::getGame() const noexcept
{
    return game;
}


unsigned int TestingRecord::getMinTestersAmount() const noexcept
{
    return game.getMinTestersAmount();
}


void TestingRecord::setMaxTestersAmount(unsigned int maxTestersAmount)
{
    if(maxTestersAmount == 0)
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


bool TestingRecord::advanceTesting()
{
    if(testingFinished)
    {
        throw TestingEndedError();
    }
    else
    {
        realTestingTime += 1;
        if(beingTested)
        {
            for(Tester &tester: testers)
            {
                effortLeft -= tester.getProductivity();
            }
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
        double effortRatio = double(realTestingEffort) / (game.getTestingTime() * 5);
        realPrice *= effortRatio;
        // 20% discount if time much longer than expected
        if(getRealTime() > 1.5 * game.getTestingTime())
        {
            realPrice *= 0.8;
        }
        return realPrice;
    }
}
