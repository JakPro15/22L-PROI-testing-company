#include "../game.h"
#include "../checkallwhitespace.h"
#include "../exceptions.h"
#include <cmath>


void Game::checkId() const
{
    if(id < minId or id > maxId)
    {
        throw InvalidId("Game", id);
    }
}


std::string Game::getUniqueName() const noexcept
{
    return "Game " + std::to_string(id - minId + 1);
}


Game::Game(char, int id, std::string title, Producer &producer, unsigned int filesSize, AbstractGame::Complexity complexity,
        unsigned int minTestersAmount, bool codeAvailable, Price marketPrice):
    id(id), title(title), producer(producer), filesSize(filesSize), complexity(complexity),
    minTestersAmount(minTestersAmount), codeAvailable(codeAvailable), marketPrice(marketPrice)
{
    // ID is not checked here - the constructor calling this constructor should handle this.
    if(checkAllWhitespace(title))
    {
        throw InvalidTitle(title);
    }
    if(filesSize == 0)
    {
        throw InvalidFilesSize();
    }
    if(minTestersAmount == 0)
    {
        throw InvalidTestersAmount();
    }
    // Also InvalidPrice can be thrown by the Price constructor.
}


Game::Game(int id, std::string title, Producer &producer, unsigned int filesSize, AbstractGame::Complexity complexity,
        unsigned int minTestersAmount, bool codeAvailable, Price marketPrice):
    Game('a', id, title, producer, filesSize, complexity, minTestersAmount, codeAvailable, marketPrice)
{
    checkId();  // Other arguments are checked in the other constructor.
}


Game::Game(int id, std::string title, Producer &producer, unsigned int filesSize, AbstractGame::Complexity complexity,
        unsigned int minTestersAmount, bool codeAvailable, int priceZl, int priceGr):
    Game(id, title, producer, filesSize, complexity, minTestersAmount, codeAvailable, Price(priceZl, priceGr))
{}


Game::~Game()
{}


int Game::getId() const noexcept
{
    return id;
}


void Game::setTitle(std::string title)
{
    if(checkAllWhitespace(title))
    {
        throw InvalidTitle(title);
    }
    else
    {
        this->title = title;
    }
}


std::string Game::getTitle() const noexcept
{
    return title;
}


void Game::setFilesSize(unsigned int filesSize)
{
    if(filesSize == 0)
    {
        throw InvalidFilesSize();
    }
    else
    {
        this->filesSize = filesSize;
    }
}


unsigned int Game::getFilesSize() const noexcept
{
    return filesSize;
}


void Game::setCodeAvailable(bool codeAvailable) noexcept
{
    this->codeAvailable = codeAvailable;
}


unsigned int Game::getCodeAvailable() const noexcept
{
    return codeAvailable;
}


void Game::setMarketPrice(Price marketPrice)
{
    this->marketPrice = marketPrice;
}


void Game::setMarketPrice(int priceZl, int priceGr)
{
    // Price constructor may throw InvalidPrice.
    this->marketPrice = Price(priceZl, priceGr);
}


Price Game::getMarketPrice() const noexcept
{
    return marketPrice;
}


void Game::setComplexity(AbstractGame::Complexity complexity)
{
    this->complexity = complexity;
}


AbstractGame::Complexity Game::getComplexity() const noexcept
{
    return complexity;
}


Producer& Game::getProducer() const noexcept
{
    return producer;
}


void Game::setMinTestersAmount(unsigned int minTestersAmount)
{
    if(minTestersAmount == 0)
    {
        throw InvalidTestersAmount();
    }
    else
    {
        this->minTestersAmount = minTestersAmount;
    }
}


unsigned int Game::getMinTestersAmount() const noexcept
{
    return minTestersAmount;
}


int Game::getTestingTime() const noexcept
{
    // In the case of a Game object no game length is available.
    // Size of the game must be estimated based on files size.
    // Estimated time: an hour per 5 MB of game files
    double testingTime = double(filesSize) / 5000;
    // Shorter time (by 20%) if source code is available.
    if(codeAvailable)
    {
        testingTime *= 0.8;
    }
    // Longer time (by 20%) for each point of complexity.
    if(complexity > 0)
    {
        testingTime *= (1 + 0.2 * complexity);
    }
    // Time increased further by 20% if many testers are needed at once.
    if(minTestersAmount > 10)
    {
        testingTime *= 1.2;
    }
    return ceil(testingTime);
}


Price Game::getTestingPrice() const noexcept
{
    // Base price - 40 zł for each expected hour of testing.
    Price testingPrice(40 * getTestingTime(), 0);
    // Discount for free games
    if(marketPrice == 0)
    {
        testingPrice *= 0.8;
    }
    // Expensive games get more expensive testing.
    else if(marketPrice > Price(100, 0))
    {
        double factor = (double(marketPrice) - 100) / 200 + 1;
        testingPrice *= factor;
    }
    return testingPrice;
}


bool Game::operator==(const Game &game) const noexcept
{
    if(id == game.getId())
    {
        return true;
    }
    else
    {
        return false;
    }
}


bool Game::operator!=(const Game &game) const noexcept
{
    return not (*this == game);
}


std::ostream& operator<<(std::ostream &stream, const Game &game) noexcept
{
    stream << game.getUniqueName();
    return stream;
}
