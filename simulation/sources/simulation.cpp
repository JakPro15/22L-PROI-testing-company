#include "../simulation.h"
#include "../../exceptions.h"
#include <iostream>

Simulation::Simulation(unsigned int iterations, unsigned int testersAmount, unsigned int managersAmount,
                        std::string producersFileName, std::string gamesFileName,
                        std::string testersFileName, std::string managersFileName,
                        std::string outFileName) try:
    out(outFileName),
    in(*this, out, producersFileName, gamesFileName, testersFileName, managersFileName),
    currentProducerRecordId(13000001),
    iterations(iterations), testersAmount(testersAmount), managersAmount(managersAmount),
    producers{}, games{}, testers{}, managers{}
{
    while(true)
    {
        try
        {
            producers.push_back(in.createProducer());
        }
        catch(const EndOfFileError& eof)
        {
            break;
        }
    }

    for(unsigned int i = 0; i < testersAmount; i++)
    {
        testers.push_back(in.createTester());
    }

    for(unsigned int i = 0; i < managersAmount; i++)
    {
        managers.push_back(in.createManager());
    }
}
catch(const std::exception& e)
{
    out << e.what();
    throw ShutdownException();
}

void Simulation::simulate()
{
    out << "Simulation ended succesfully";
}

TestingCompany& Simulation::getTestingCompany() noexcept
{
    return testingCompany;
}

int Simulation::getProducerRecordId()
{
    int return_id  = currentProducerRecordId++;
    if (return_id > 13999999)
    {
        throw InvalidId("producer record", return_id);
    }
    return return_id;
}

AbstractGame& Simulation::getNewGame(Producer& producer)
{
    try
    {
        std::shared_ptr<AbstractGame> game = in.createGame(producer);
        games.push_back(game);
        return *game;
    }
    catch(const std::exception& e)
    {
        out << e.what();
        throw ShutdownException();
    }
    
}

bool Simulation::operator==(const Simulation &simulation) const noexcept
{
    return this == &simulation;
}

bool Simulation::operator!=(const Simulation &simulation) const noexcept
{
    return not (*this == simulation);
}

std::ostream& operator<<(std::ostream& os, const Simulation& simulation) noexcept
{
    os << "simulation";
    return os;
}