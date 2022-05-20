#include "../roleplayinggame.h"
#include "../../exceptions.h"
#include <cmath>


void RolePlayingGame::checkId() const
{
    if(id < minId or id > maxId)
    {
        throw InvalidId("RolePlayingGame", id);
    }
}


std::string RolePlayingGame::getUniqueName() const noexcept
{
    return "RolePlayingGame " + std::to_string(id - minId + 1);
}


RolePlayingGame::RolePlayingGame(int id, std::string title, Producer &producer, unsigned int filesSize,
                                 AbstractGame::Complexity complexity, unsigned int minTestersAmount, int length,
                                 int fullLength, bool codeAvailable, Price marketPrice):
    Game('a', id, title, producer, filesSize, complexity, minTestersAmount, codeAvailable, marketPrice),
    length(length), fullLength(fullLength)
{
    checkId();  // Different checkId than the one in Game::Game regular (public) constructor
    if(length == 0)
    {
        throw InvalidLength();
    }
    if(fullLength < length)
    {
        throw InvalidFullLength(length, fullLength);
    }
}


RolePlayingGame::RolePlayingGame(int id, std::string title, Producer &producer, unsigned int filesSize,
                                 AbstractGame::Complexity complexity, unsigned int minTestersAmount, int length,
                                 int fullLength, bool codeAvailable, int priceZl, int priceGr):
    RolePlayingGame(id, title, producer, filesSize, complexity, minTestersAmount, length, fullLength, codeAvailable,
                    Price(priceZl, priceGr))
{}


RolePlayingGame::~RolePlayingGame()
{}


void RolePlayingGame::setLength(unsigned int length)
{
    if(length == 0)
    {
        throw InvalidLength();
    }
    else if(length > fullLength)
    {
        throw InvalidFullLength(length, fullLength);
    }
    else
    {
        this->length = length;
    }
}


unsigned int RolePlayingGame::getLength() const noexcept
{
    return length;
}


void RolePlayingGame::setFullLength(unsigned int fullLength)
{
    if(length > fullLength)
    {
        throw InvalidFullLength(length, fullLength);
    }
    else
    {
        this->fullLength = fullLength;
    }
}


unsigned int RolePlayingGame::getFullLength() const noexcept
{
    return fullLength;
}


int RolePlayingGame::getTestingTime() const noexcept
{
    // Estimated time: 3x the average of the time to complete the game and the time to fully experience the game
    // + an hour per 5 MB of game files
    double testingTime = ((length + fullLength) / 2) / 20 + filesSize / 5000;
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


Price RolePlayingGame::getTestingPrice() const noexcept
{
    Price testingPrice = Game::getTestingPrice();
    // Difference from Game class: more expensive testing if many people are needed at once.
    if(minTestersAmount > 20)
    {
        testingPrice *= 1.2;
    }
    else if(minTestersAmount > 10)
    {
        testingPrice *= 1.1;
    }
    return testingPrice;
}


bool RolePlayingGame::operator==(const RolePlayingGame &game) const noexcept
{
    if(id == game.id)
    {
        return true;
    }
    else
    {
        return false;
    }
}


bool RolePlayingGame::operator!=(const RolePlayingGame &game) const noexcept
{
    return not (*this == game);
}


std::ostream& operator<<(std::ostream &stream, const RolePlayingGame &game) noexcept
{
    stream << game.getUniqueName();
    return stream;
}
