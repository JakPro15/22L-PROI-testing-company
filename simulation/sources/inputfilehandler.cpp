#include "../inputfilehandler.h"
#include "../../exceptions.h"
#include "../../games/competitivegame.h"
#include "../../games/puzzle.h"
#include "../../games/roleplayinggame.h"
#include "../simulation.h"


void InputFileHandler::checkId() const
{
    if(id < minId or id > maxId)
    {
        throw InvalidId("InputFileHandler", id);
    }
}

void InputFileHandler::getlineWithEOFCheck(std::ifstream& file, std::string& string)
{
    if(file.eof())
    {
        throw EndOfFileError();
    }
    std::getline(file, string);
}

InputFileHandler::InputFileHandler(int id,
    Simulation& sim, OutputHandler& out,
    std::string producersFileName, std::string gamesFileName,
    std::string testersFileName, std::string managersFileName):
        id(id), sim(sim), out(out), producers(0), games(0), competetiveGames(0),
        infiniteGames(0), puzzles(0), roleplayingGames(0), testers(0), managers(0)
{
    checkId();

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
    if(id > Producer::maxId)
    {
        throw InvalidId("producer", id);
    }
    producers++;

    std::string name;
    getlineWithEOFCheck(producersFile, name);

    std::string streetName;
    getlineWithEOFCheck(producersFile, streetName);

    std::string strhouseNumber;
    getlineWithEOFCheck(producersFile, strhouseNumber);
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
    getlineWithEOFCheck(producersFile, strapartmentNumber);
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
    getlineWithEOFCheck(producersFile, cityName);

    std::string postCode;
    getlineWithEOFCheck(producersFile, postCode);

    TestingCompany& testingCompany = sim.getTestingCompany();

    Address address(streetName, houseNumber, apartmentNumber, cityName, postCode);
    std::shared_ptr<Producer> producer = std::make_shared<Producer>(out, id, name, address, sim, testingCompany);
    out << *this << " creates " << *producer << OutputHandler::endlWait;
    return producer;
}

std::shared_ptr<AbstractGame> InputFileHandler::createGame(Producer& producer, bool loop)
{
    std::string gameType;

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

    try
    {
        getlineWithEOFCheck(gamesFile, gameType);

        getlineWithEOFCheck(gamesFile, title);

        getlineWithEOFCheck(gamesFile, strfilesSize);
        try
        {
            filesSize = std::stoi(strfilesSize);
        }
        catch(const std::exception& e)
        {
            throw ConversionError(strfilesSize, "int");
        }

        getlineWithEOFCheck(gamesFile, strcomplexity);
        try
        {
            intcomplexity = std::stoi(strcomplexity);
            complexity = static_cast<AbstractGame::Complexity>(intcomplexity);
        }
        catch(const std::exception& e)
        {
            throw ConversionError(strcomplexity, "AbstractGame::Complexity");
        }

        getlineWithEOFCheck(gamesFile, strminTestersAmount);
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
            getlineWithEOFCheck(gamesFile, strdepth);
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
            getlineWithEOFCheck(gamesFile, strserverSize);
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
            getlineWithEOFCheck(gamesFile, strdifficulty);
            try
            {
                intdifficulty = std::stoi(strdifficulty);
                difficulty = static_cast<Puzzle::Difficulty>(intdifficulty);
            }
            catch(const std::exception& e)
            {
                throw ConversionError(strdifficulty, "Puzzle::Difficulty");
            }

            getlineWithEOFCheck(gamesFile, strlength);
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
            getlineWithEOFCheck(gamesFile, strlength);
            try
            {
                length = std::stoi(strlength);
            }
            catch(const std::exception& e)
            {
                throw ConversionError(strlength, "int");
            }

            getlineWithEOFCheck(gamesFile, strfullLength);
            try
            {
                fullLength = std::stoi(strfullLength);
            }
            catch(const std::exception& e)
            {
                throw ConversionError(strfullLength, "int");
            }
        }

        getlineWithEOFCheck(gamesFile, strcodeAvailable);
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

        getlineWithEOFCheck(gamesFile, strpriceZl);
        try
        {
            priceZl = std::stoi(strpriceZl);
        }
        catch(const std::exception& e)
        {
            throw ConversionError(strpriceZl, "int");
        }

        getlineWithEOFCheck(gamesFile, strpriceGr);
        try
        {
            priceGr = std::stoi(strpriceGr);
        }
        catch(const std::exception& e)
        {
            throw ConversionError(strpriceGr, "int");
        }
    }
    catch(const EndOfFileError& eof)
    {
        if(loop)
        {
            throw EndOfFileError();
        }
        gamesFile.clear();
        gamesFile.seekg(0);
        return createGame(producer, true);
    }

    if(gameType == "competitive")
    {
        id = CompetitiveGame::minId + competetiveGames;
        competetiveGames++;
        std::shared_ptr<AbstractGame> game = std::make_shared<CompetitiveGame>(
            id, title, producer, filesSize, complexity, minTestersAmount, depth, serverSize, codeAvailable, priceZl, priceGr
        );
        out << *this << " creates " << *game << OutputHandler::endlWait;
        return game;
    }
    else if(gameType == "normal")
    {
        id = Game::minId + games;
        games++;
        std::shared_ptr<AbstractGame> game = std::make_unique<Game>(
            id, title, producer, filesSize, complexity, minTestersAmount, codeAvailable, priceZl, priceGr
        );
        out << *this << " creates " << *game << OutputHandler::endlWait;
        return game;
    }
    else if(gameType == "infinite")
    {
        id = InfiniteGame::minId + infiniteGames;
        infiniteGames++;
        std::shared_ptr<AbstractGame> game = std::make_unique<InfiniteGame>(
            id, title, producer, filesSize, complexity, minTestersAmount, depth, codeAvailable, priceZl, priceGr
            );
        out << *this << " creates " << *game << OutputHandler::endlWait;
        return game;
    }
    else if(gameType == "puzzle")
    {
        id = Puzzle::minId + puzzles;
        puzzles++;
        std::shared_ptr<AbstractGame> game = std::make_unique<Puzzle>(
            id, title, producer, filesSize, complexity, minTestersAmount, difficulty, length, codeAvailable, priceZl, priceGr
            );
        out << *this << " creates " << *game << OutputHandler::endlWait;
        return game;
    }
    else if(gameType == "roleplaying")
    {
        id = RolePlayingGame::minId + roleplayingGames;
        roleplayingGames++;
        std::shared_ptr<AbstractGame> game = std::make_unique<RolePlayingGame>(
            id, title, producer, filesSize, complexity, minTestersAmount, length, fullLength, codeAvailable, priceZl, priceGr);
        out << *this << " creates " << *game << OutputHandler::endlWait;
        return game;
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

    getlineWithEOFCheck(testersFile, name);

    std::string surname;

    getlineWithEOFCheck(testersFile, surname);

    TestingCompany& testingCompany = sim.getTestingCompany();

    std::unique_ptr<Tester> tester = std::make_unique<Tester>(id, name, surname, testingCompany, out);
    out << *this << " creates " << *tester << OutputHandler::endlWait;
    return tester;
}

std::shared_ptr<Manager> InputFileHandler::createManager()
{
    int id = Manager::minId + managers;
    managers++;

    std::string name;
    getlineWithEOFCheck(managersFile, name);

    std::string surname;
    getlineWithEOFCheck(managersFile, surname);

    TestingCompany& testingCompany = sim.getTestingCompany();

    std::unique_ptr<Manager> manager = std::make_unique<Manager>(id, name, surname, testingCompany, out);
    out << *this << " creates " << *manager << OutputHandler::endlWait;
    return manager;
}


std::ostream& operator<<(std::ostream& os, const InputFileHandler& handler) noexcept
{
    os << "InputFileHandler " << handler.id - handler.minId + 1;
    return os;
}
