#include "../inputfilehandler.h"
#include "../../exceptions.h"


InputFileHandler::InputFileHandler(
    Simulation& sim, OutputHandler& out,
    std::string producersFileName, std::string gamesFileName,
    std::string testersFileName, std::string managersFileName):
        sim(sim), out(out), producers(0), games(0), competetiveGames(0), infiniteGames(0), roleplayingGames(0), testers(0), managers(0)
{
    producersFile.open(producersFileName);
    if(!producersFile)
    {
        throw FileError(producersFileName);
    }

    gamesFile.open(gamesFileName);
    if(!gamesFile)
    {
        throw FileError(gamesFileName);
    }

    testersFile.open(testersFileName);
    if(!testersFile)
    {
        throw FileError(testersFileName);
    }

    managersFile.open(managersFileName);
    if(!managersFile)
    {
        throw FileError(managersFileName);
    }
}

InputFileHandler::~InputFileHandler()
{
    producersFile.close();
    gamesFile.close();
    testersFile.close();
    managersFile.close();
}

std::shared_ptr<Producer> InputFileHandler::createProducer()
{
    int id = 14000001 + producers;

    std::string name;
    std::getline(producersFile, name);

    std::string streetName;
    std::getline(producersFile, streetName);

    std::string strhouseNumber;
    std::getline(producersFile, strhouseNumber);
    unsigned int houseNumber;
    try
    {
        houseNumber = std::stoi(strhouseNumber);
    }
    catch(const std::exception& e)
    {
        throw ConversionError(strhouseNumber);
    }

    std::string strapartmentNumber;
    std::getline(producersFile, strapartmentNumber);
    unsigned int apartmentNumber;
    try
    {
        apartmentNumber = std::stoi(strapartmentNumber);
    }
    catch(const std::exception& e)
    {
        throw ConversionError(strapartmentNumber);
    }
    

    std::string cityName;
    std::getline(producersFile, cityName);

    std::string postCode;
    std::getline(producersFile, postCode);

    TestingCompany& testingCompany = sim.getTestingCompany();

    Address address(streetName, houseNumber, apartmentNumber, cityName, postCode);
    return std::make_shared<Producer>(out, id, name, address, sim, testingCompany);
}

std::shared_ptr<AbstractGame> InputFileHandler::createGame()
{

}

std::shared_ptr<Tester> InputFileHandler::createTester()
{

}

std::shared_ptr<Manager> InputFileHandler::createManager()
{

}