#include "../simulation.h"
#include "../../exceptions.h"
#include <iostream>

Simulation::Simulation(unsigned int testersAmount, unsigned int managersAmount,
                        std::string producersFileName, std::string gamesFileName,
                        std::string testersFileName, std::string managersFileName,
                        std::string outFileName) try:
    out(outFileName),
    in(*this, out, producersFileName, gamesFileName, testersFileName, managersFileName),
    currentProducerRecordId(13000001),
    testersAmount(testersAmount), managersAmount(managersAmount), testingCompany(out, {}, {}),
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
        std::shared_ptr<Tester> newTester = in.createTester();
        testers.push_back(newTester);
        testingCompany.addTester(newTester);
    }

    for(unsigned int i = 0; i < managersAmount; i++)
    {
        std::shared_ptr<Manager> newManager = in.createManager();
        managers.push_back(newManager);
        testingCompany.addManager(newManager);
    }
}
catch(const std::exception& e)
{
    out << e.what();
    throw ShutdownException();
}

void Simulation::simulate(unsigned int iterations)
{
    out << "Simulation ended succesfully" << OutputHandler::endlWait;
}

TestingCompany& Simulation::getTestingCompany() noexcept
{
    return testingCompany;
}

int Simulation::getProducerRecordId()
{
    int returnId  = currentProducerRecordId++;
    if (returnId > 13999999)
    {
        throw InvalidId("producer record", returnId);
    }
    return returnId;
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