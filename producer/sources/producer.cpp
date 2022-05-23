#include "../producer.h"
#include "../../testingcompany/checkallwhitespace.h"
#include "../../exceptions.h"
#include "../../simulation/simulation.h"
#include "../../games/abstractgame.h"
#include <cstdlib>
#include <sstream>


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
    std::stringstream stringstr;
    stringstr << *this << " requests an ID for a new ProducerDatabase::Record from " << simulation;
    out << stringstr.str();
    return simulation.getProducerRecordId();
}


void Producer::payForTesting(AbstractGame &game)
{
    std::stringstream stringstr;
    stringstr << *this << " pays for " << game << " to " << testingCompany;
    out << stringstr.str();
    testingCompany.paymentDone(game);
}


void Producer::advanceTime()
{
    // 1% chance per hour for the producer to make a new game.
    if(double(std::rand()) / RAND_MAX < 0.01)
    {
        AbstractGame &game = simulation.getNewGame();
        database.addGame(game);
        std::stringstream stringstr;
        stringstr << *this << " creates " << game << " (requested from " << simulation << ")";
        out << stringstr.str();
    }

    // 5% chance per hour for the producer to send a testing request.
    if(database.getUntestedGamesAmount() > 0)
    {
        if(double(std::rand()) / RAND_MAX < 0.01)
        {
            AbstractGame &gameToTest = database.getGameToBeTested();
            testingCompany.sendTestingRequest(gameToTest);
            std::stringstream stringstr;
            stringstr << *this << " requests testing of " << gameToTest << " by " << testingCompany;
            out << stringstr.str();
        }
    }
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
