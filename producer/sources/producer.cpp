#include "../producer.h"
#include "../../testingcompany/checkallwhitespace.h"
#include "../../exceptions.h"
#include "../../simulation/simulation.h"
#include <cstdlib>


void Producer::checkId() const
{
    if(id < minId or id > maxId)
    {
        throw InvalidId("Producer", id);
    }
}


Producer::Producer(int id, std::string name, Address address, Simulation &simulation, TestingCompany &testingCompany):
    name(name), address(address), database(id - Producer::minId + ProducerDatabase::minId, *this), id(id),
    simulation(simulation), testingCompany(testingCompany)
{
    checkId();
    if(checkAllWhitespace(name))
    {
        throw EmptyNameException("Produecer company name");
    }
}


void Producer::setName(std::string name)
{
    if(checkAllWhitespace(name))
    {
        throw EmptyNameException("Produecer company name");
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
    return simulation.getProducerRecordId();
}


void Producer::payForTesting(AbstractGame &game)
{
    testingCompany.paymentDone(game);
}


void Producer::advanceTime()
{
    // 1% chance per hour for the producer to make a new game.
    if(double(std::rand()) / RAND_MAX < 0.01)
    {
        database.addGame(simulation.getNewGame());
    }

    // 5% chance per hour for the producer to send a testing request.
    if(database.getUntestedGamesAmount() > 0)
    {
        if(double(std::rand()) / RAND_MAX < 0.01)
        {
            AbstractGame &gameToTest = database.getGameToBeTested();
            testingCompany.sendTestingRequest(gameToTest);
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
