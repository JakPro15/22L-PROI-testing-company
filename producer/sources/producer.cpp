#include "../producer.h"
#include "../../testingcompany/checkallwhitespace.h"
#include "../../exceptions.h"
#include "../../simulation/simulation.h"
#include "../../games/abstractgame.h"
#include <chrono>
#include <random>


void Producer::checkId() const
{
    if(id < minId or id > maxId)
    {
        throw InvalidId("Producer", id);
    }
}


Producer::Producer(OutputHandler &out, int id, std::string name, Address address, Simulation &simulation, TestingCompany &testingCompany):
    out(out), name(name), address(address), database(out, id - Producer::minId + ProducerDatabase::minId, *this), id(id),
    simulation(simulation), testingCompany(testingCompany)
{
    checkId();
    if(checkAllWhitespace(name))
    {
        throw EmptyNameException("Producer company name");
    }
}


void Producer::setName(std::string name)
{
    if(checkAllWhitespace(name))
    {
        throw EmptyNameException("Producer company name");
    }
    else
    {
        this->name = name;
    }
}


std::string Producer::getName() const noexcept
{
    return name;
}


void Producer::setAddress(Address address) noexcept
{
    this->address = address;
}


Address Producer::getAddress() const noexcept
{
    return address;
}


int Producer::getRecordId() noexcept
{
    out << *this << " requests an ID for a new ProducerDatabase::Record from " << simulation
        << OutputHandler::endlWait;
    return simulation.getProducerRecordId();
}


void Producer::payForTesting(AbstractGame &game)
{
    out << *this << " pays for " << game << " to " << testingCompany << OutputHandler::endlWait;
    testingCompany.paymentDone(game);
}


void Producer::advanceTime()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator (seed);
    // 10% chance per hour for the producer to make a new game.
    if(double(generator()) / generator.max() < 0.1 or database.getTotalGamesAmount() == 0)
    {
        out << *this << " requests a new game from " << simulation << OutputHandler::endlWait;
        AbstractGame &game = simulation.getNewGame(*this);
        database.addGame(game);
        out << *this << " has made " << game << OutputHandler::endlWait;
    }

    // 20% chance per hour for the producer to send a testing request.
    if(database.getUntestedGamesAmount() > 0)
    {
        if(double(generator()) / generator.max() < 0.2)
        {
            AbstractGame &gameToTest = database.getGameToBeTested();
            out << *this << " requests testing of " << gameToTest << " by " << testingCompany
                << OutputHandler::endlWait;
            testingCompany.obtainTestingRequest(gameToTest);
        }
    }
}


void Producer::testingFinished(const AbstractGame& game, Price price)
{
    out << *this << " receives notification that " << game << "'s testing has been finished" << OutputHandler::endlWait;
    database.gameFinishedTesting(game, price);
}


bool Producer::operator==(const Producer &producer) const noexcept
{
    return id == producer.id;
}


bool Producer::operator!=(const Producer &producer) const noexcept
{
    return not (*this == producer);
}


std::ostream& operator<<(std::ostream &stream, const Producer &producer) noexcept
{
    stream << "Producer " << producer.id - producer.minId + 1;
    return stream;
}
