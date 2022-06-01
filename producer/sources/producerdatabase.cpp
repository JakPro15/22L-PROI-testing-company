#include "../producerdatabase.h"
#include "../producer.h"
#include "../../testingcompany/testingrecord.h"
#include "../../exceptions.h"
#include "../../games/abstractgame.h"
#include "../../simulation/outputhandler.h"
#include <algorithm>
#include <chrono>
#include <random>


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

std::string ProducerDatabase::Record::getUniqueName() const noexcept
{
    return "ProducerDatabase::Record " + std::to_string(id - minId + 1);
}


int ProducerDatabase::findGame(const AbstractGame &game)
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


ProducerDatabase::ProducerDatabase(OutputHandler &out, int id, Producer &producer): out(out), id(id), producer(producer)
{
    checkId();
}


void ProducerDatabase::addGame(AbstractGame &game)
{
    if(game.producer != producer)
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
            Record record(producer.getRecordId(), game);
            out << *this << " adds " << game << " to itself, enclosed in " << record.getUniqueName()
                << OutputHandler::endlWait;
            games.push_back(std::move(record));  // to signify that the record is moved, not copied (no ID duplication).
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
                out << *this << " notices " << record.game << "stored in " << record.getUniqueName()
                    << " should be paid for" << OutputHandler::endlWait;
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


unsigned int ProducerDatabase::getTotalGamesAmount() const noexcept
{
    return games.size();
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
        out << *this << " prepares " << iterator->game << " to be tested, at request of " << producer
            << OutputHandler::endlWait;
        iterator->testingRequested = true;
        return iterator->game;
    }
}


void ProducerDatabase::gameFinishedTesting(const AbstractGame& game, Price price)
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator (seed);
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
        out << *this << " registers that " << game << "'s testing has been finished" << OutputHandler::endlWait;
        games[index].tested = true;
        games[index].price = price;
        games[index].timeUntilPaid = generator() % 100 + 1;
    }
}

std::ostream& operator<<(std::ostream &stream, const ProducerDatabase &database) noexcept
{
    stream << "ProducerDatabase " << database.id - database.minId + 1;
    return stream;
}
