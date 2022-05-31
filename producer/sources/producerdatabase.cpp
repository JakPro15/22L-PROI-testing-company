#include "../producerdatabase.h"
#include "../producer.h"
#include "../../testingcompany/testingrecord.h"
#include "../../exceptions.h"
#include "../../games/abstractgame.h"
#include "../../simulation/outputhandler.h"
#include <algorithm>
#include <sstream>
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
            std::stringstream stringstr;
            Record record(producer.getRecordId(), game);
            stringstr << *this << " adds " << game << " to itself, enclosed in " << record.getUniqueName();
            out << stringstr.str();
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
                std::stringstream stringstr;
                stringstr << *this << " notices " << record.game << "stored in " << record.getUniqueName()
                          << " should be paid for";
                out << stringstr.str();
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
        std::stringstream stringstr;
        stringstr << *this << " prepares " << iterator->game << " to be tested, at request of " << producer;
        out << stringstr.str();
        iterator->testingRequested = true;
        return iterator->game;
    }
}


void ProducerDatabase::gameFinishedTesting(AbstractGame& game)
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
        std::stringstream stringstr;
        stringstr << *this << " notices " << game << "'s testing has been finished";
        out << stringstr.str();
        games[index].tested = true;
        games[index].timeUntilPaid = generator() % 100 + 1;
    }
}

std::ostream& operator<<(std::ostream &stream, const ProducerDatabase &database) noexcept
{
    stream << "ProducerDatabase " << database.id - database.minId + 1;
    return stream;
}
