#include "../producerdatabase.h"
#include "../producer.h"
#include "../../exceptions.h"
#include <algorithm>
#include <cstdlib>


void ProducerDatabase::checkId() const
{
    if(id < minId or id > maxId)
    {
        throw InvalidId("ProducerDatabase", id);
    }
}


void ProducerDatabase::Record::checkId() const
{
    if(id < minId or id > maxId)
    {
        throw InvalidId("ProducerDatabase::Record", id);
    }
}


ProducerDatabase::Record::Record(int id, AbstractGame &game): id(id), game(game), testingRequested(false),
    tested(false), timeUntilPaid(0)
{
    checkId();
}


int ProducerDatabase::findGame(AbstractGame &game)
{
    auto iterator = std::find_if(games.begin(), games.end(), [&game](Record &record) {return record.game == game;});
    if(iterator == games.end())
    {
        return -1;
    }
    else
    {
        return iterator - games.begin();
    }
}


ProducerDatabase::ProducerDatabase(int id, Producer &producer): id(id), producer(producer)
{
    checkId();
}


void ProducerDatabase::addGame(AbstractGame &game)
{
    if(game.getProducer() != producer)
    {
        throw InvalidProducer();
    }
    else
    {
        if(findGame(game) != -1)
        {
            throw DuplicateGameError();
        }
        else
        {
            games.push_back(Record(producer.getRecordId(), game));
        }
    }
}


void ProducerDatabase::checkPayments()
{
    for(Record &record: games)
    {
        if(record.tested and (record.timeUntilPaid > 0))
        {
            record.timeUntilPaid--;
            if(record.timeUntilPaid == 0)
            {
                producer.payForTesting(record.game);
            }
        }
    }
}


unsigned int ProducerDatabase::getUntestedGamesAmount() const noexcept
{
    unsigned int counter = 0;
    for(const Record &record: games)
    {
        if(not record.testingRequested)
        {
            counter++;
        }
    }
    return counter;
}


AbstractGame& ProducerDatabase::getGameToBeTested()
{
    auto iterator = std::find_if(games.begin(), games.end(), [](Record &record) {return not record.testingRequested;});
    if(iterator == games.end())
    {
        throw NoGamesUntestedError();
    }
    else
    {
        iterator->testingRequested = true;
        return iterator->game;
    }
}


void ProducerDatabase::gameFinishedTesting(AbstractGame& game)
{
    int index = findGame(game);
    if(index == -1)
    {
        throw GameNotPresentError();
    }
    else if(games[index].tested)
    {
        throw GameAlreadyTestedError();
    }
    else if(not games[index].testingRequested)
    {
        throw GameNotRequestedError();
    }
    else
    {
        games[index].tested = true;
        games[index].timeUntilPaid = std::rand() % 100 + 1;
    }
}