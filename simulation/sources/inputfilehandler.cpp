#include "../inputfilehandler.h"
#include "../../exceptions.h"
#include "../../games/competitivegame.h"
#include "../../games/puzzle.h"
#include "../../games/roleplayinggame.h"


InputFileHandler::InputFileHandler(
    Simulation& sim, OutputHandler& out,
    std::string producersFileName, std::string gamesFileName,
    std::string testersFileName, std::string managersFileName):
        sim(sim), out(out), producers(0), games(0), competetiveGames(0),
        infiniteGames(0), puzzles(0), roleplayingGames(0), testers(0), managers(0)
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
    int id = Producer::minId + producers;
    producers++;

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
        throw ConversionError(strhouseNumber, "int");
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
        throw ConversionError(strapartmentNumber, "int");
    }
    

    std::string cityName;
    std::getline(producersFile, cityName);

    std::string postCode;
    std::getline(producersFile, postCode);

    TestingCompany& testingCompany = sim.getTestingCompany();

    Address address(streetName, houseNumber, apartmentNumber, cityName, postCode);
    return std::make_shared<Producer>(out, id, name, address, sim, testingCompany);
}

std::shared_ptr<AbstractGame> InputFileHandler::createGame(Producer& producer)
{
    std::string gameType;
    std::getline(gamesFile, gameType);

    int id;
    std::string title;
    std::string strfilesSize;
    unsigned int filesSize;
    std::string strcomplexity;
    int intcomplexity;
    AbstractGame::Complexity complexity;
    std::string strminTestersAmount;
    unsigned int minTestersAmount;
    std::string strdepth;
    int intdepth;
    InfiniteGame::Depth depth;
    std::string strserverSize;
    unsigned int serverSize;
    std::string strcodeAvailable;
    bool codeAvailable;
    std::string strpriceZl;
    int priceZl;
    std::string strpriceGr;
    int priceGr;
    std::string strdifficulty;
    int intdifficulty;
    Puzzle::Difficulty difficulty;
    std::string strlength;
    unsigned int length;
    std::string strfullLength;
    unsigned int fullLength;

    std::getline(gamesFile, title);

    std::getline(gamesFile, strfilesSize);
    try
    {
        filesSize = std::stoi(strfilesSize);
    }
    catch(const std::exception& e)
    {
        throw ConversionError(strfilesSize, "int");
    }

    std::getline(gamesFile, strcomplexity);
    try
    {
        intcomplexity = std::stoi(strcomplexity);
        complexity = static_cast<AbstractGame::Complexity>(intcomplexity);
    }
    catch(const std::exception& e)
    {
        throw ConversionError(strcomplexity, "AbstractGame::Complexity");
    }

    std::getline(gamesFile, strminTestersAmount);
    try
    {
        minTestersAmount = std::stoi(strminTestersAmount);
    }
    catch(const std::exception& e)
    {
        throw ConversionError(strminTestersAmount, "int");
    }

    if ((gameType == "infinite") || (gameType == "competitive"))
    {
        std::getline(gamesFile, strdepth);
        try
        {
            intdepth = std::stoi(strdepth);
            depth = static_cast<InfiniteGame::Depth>(intdepth);
        }
        catch(const std::exception& e)
        {
            throw ConversionError(strdepth, "InfiniteGame::Depth");
        }
    }
    if (gameType == "competitive")
    {
        std::getline(gamesFile, strserverSize);
        try
        {
            serverSize = std::stoi(strserverSize);
        }
        catch(const std::exception& e)
        {
            throw ConversionError(strserverSize, "int");
        }
    }
    else if (gameType == "puzzle")
    {
        std::getline(gamesFile, strdifficulty);
        try
        {
            intdifficulty = std::stoi(strdifficulty);
            difficulty = static_cast<Puzzle::Difficulty>(intdifficulty);
        }
        catch(const std::exception& e)
        {
            throw ConversionError(strdifficulty, "Puzzle::Difficulty");
        }

        std::getline(gamesFile, strlength);
        try
        {
            length = std::stoi(strlength);
        }
        catch(const std::exception& e)
        {
            throw ConversionError(strlength, "int");
        }
    }
    else if (gameType == "roleplaying")
    {
        std::getline(gamesFile, strlength);
        try
        {
            length = std::stoi(strlength);
        }
        catch(const std::exception& e)
        {
            throw ConversionError(strlength, "int");
        }

        std::getline(gamesFile, strfullLength);
        try
        {
            fullLength = std::stoi(strfullLength);
        }
        catch(const std::exception& e)
        {
            throw ConversionError(strfullLength, "int");
        }
    }

    std::getline(gamesFile, strcodeAvailable);
    if (strcodeAvailable == "true")
    {
        codeAvailable = true;
    }
    else if (strcodeAvailable == "false")
    {
        codeAvailable = false;
    }
    else
    {
        throw ConversionError(strcodeAvailable, "bool");
    }

    std::getline(gamesFile, strpriceZl);
    try
    {
        priceZl = std::stoi(strpriceZl);
    }
    catch(const std::exception& e)
    {
        throw ConversionError(strpriceZl, "int");
    }

    std::getline(gamesFile, strpriceGr);
    try
    {
        priceZl = std::stoi(strpriceGr);
    }
    catch(const std::exception& e)
    {
        throw ConversionError(strpriceGr, "int");
    }

    if(gameType == "competitive")
    {
        id = CompetitiveGame::minId + competetiveGames;
        competetiveGames++;
        return std::make_shared<CompetitiveGame>(
            id, title, producer, filesSize, complexity, minTestersAmount, depth, serverSize, codeAvailable, priceZl, priceGr
            );
    }
    else if(gameType == "normal")
    {
        id = Game::minId + games;
        games++;
        return std::make_unique<Game>(
            id, title, producer, filesSize, complexity, minTestersAmount, codeAvailable, priceZl, priceGr
            );
    }
    else if(gameType == "infinite")
    {
        id = InfiniteGame::minId + infiniteGames;
        infiniteGames++;
        return std::make_unique<InfiniteGame>(
            id, title, producer, filesSize, complexity, minTestersAmount, depth, codeAvailable, priceZl, priceGr
            );
    }
    else if(gameType == "puzzle")
    {
        id = Puzzle::minId + puzzles;
        puzzles++;
        return std::make_unique<Puzzle>(
            id, title, producer, filesSize, complexity, minTestersAmount, difficulty, length, codeAvailable, priceZl, priceGr
            );
    }
    else if(gameType == "roleplaying")
    {
        id = RolePlayingGame::minId + roleplayingGames;
        roleplayingGames++;
        return std::make_unique<RolePlayingGame>(
            id, title, producer, filesSize, complexity, minTestersAmount, length, fullLength, codeAvailable, priceZl, priceGr);
    }
    else
    {
        throw FileError('a', "Malformed file containing game data");
    }
}

std::shared_ptr<Tester> InputFileHandler::createTester()
{
    int id = Tester::minId + testers;
    testers++;
    
    std::string name;
    std::getline(testersFile, name);

    std::string surname;
    std::getline(testersFile, surname);

    return std::make_unique<Tester>(id, name, surname);
}

std::shared_ptr<Manager> InputFileHandler::createManager()
{
    int id = Manager::minId + managers;
    managers++;
    
    std::string name;
    std::getline(testersFile, name);

    std::string surname;
    std::getline(testersFile, surname);

    TestingCompany& company = sim.getTestingCompany();

    return std::make_unique<Manager>(id, name, surname, company);
}