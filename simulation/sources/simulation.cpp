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
    out << e.what() << OutputHandler::endlWait;
    throw ShutdownException();
}

void Simulation::simulate(unsigned int iterations)
{
    try
    {
        for(unsigned int i = 0; i < iterations; i++)
        {
            for(std::shared_ptr<Producer> producer: producers)
            {
                producer->advanceTime();
            }
            testingCompany.advanceTime();
        }
        out << *this << " ended succesfully" << OutputHandler::endlWait;
    }
    catch(const std::exception& e)
    {
        out << e.what() << OutputHandler::endlWait;
        throw ShutdownException();
    }
}

TestingCompany& Simulation::getTestingCompany() noexcept
{
    return testingCompany;
}

int Simulation::getProducerRecordId()
{
    int returnId  = currentProducerRecordId++;
    return returnId;
}

AbstractGame& Simulation::getNewGame(Producer& producer)
{
    try
    {
        std::shared_ptr<AbstractGame> game = in.createGame(producer, false);
        games.push_back(game);
        return *game;
    }
    catch(const std::exception& e)
    {
        out << e.what() << OutputHandler::endlWait;
        throw FileError('a', "Malformed games file.");
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
    os << "Simulation";
    return os;
}