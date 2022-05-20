#include "../infinitegame.h"
#include "../../exceptions.h"
#include <cmath>


void InfiniteGame::checkId() const
{
    if(id < minId or id > maxId)
    {
        throw InvalidId("InfiniteGame", id);
    }
}


std::string InfiniteGame::getUniqueName() const noexcept
{
    return "InfiniteGame " + std::to_string(id - minId + 1);
}


InfiniteGame::InfiniteGame(char, int id, std::string title, Producer &producer, unsigned int filesSize,
                           AbstractGame::Complexity complexity, unsigned int minTestersAmount, Depth depth,
                           bool codeAvailable, Price marketPrice):
    Game('a', id, title, producer, filesSize, complexity, minTestersAmount, codeAvailable, marketPrice), depth(depth)
{}


InfiniteGame::InfiniteGame(int id, std::string title, Producer &producer, unsigned int filesSize,
                           AbstractGame::Complexity complexity, unsigned int minTestersAmount, Depth depth,
                           bool codeAvailable, Price marketPrice):
    InfiniteGame('a', id, title, producer, filesSize, complexity, minTestersAmount, depth, codeAvailable, marketPrice)
{
    checkId();  // Different checkId than the one in Game::Game regular (public) constructor
}


InfiniteGame::InfiniteGame(int id, std::string title, Producer &producer, unsigned int filesSize,
                           AbstractGame::Complexity complexity, unsigned int minTestersAmount, Depth depth,
                           bool codeAvailable, int priceZl, int priceGr):
    InfiniteGame(id, title, producer, filesSize, complexity, minTestersAmount, depth, codeAvailable, Price(priceZl, priceGr))
{}


InfiniteGame::~InfiniteGame()
{}


void InfiniteGame::setDepth(Depth depth) noexcept
{
    this->depth = depth;
}


InfiniteGame::Depth InfiniteGame::getDepth() const noexcept
{
    return depth;
}


int InfiniteGame::getTestingTime() const noexcept
{
    // Estimated time: an hour per 5 MB of game files
    double testingTime = filesSize / 5000;
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
    // Time modified similarly by depth (30% per point).
    testingTime *= (1 + 0.3 * depth);
    // Time increased further by 20% if many testers are needed at once.
    if(minTestersAmount > 10)
    {
        testingTime *= 1.2;
    }
    return ceil(testingTime);
}


bool InfiniteGame::operator==(const InfiniteGame &game) const noexcept
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


bool InfiniteGame::operator!=(const InfiniteGame &game) const noexcept
{
    return not (*this == game);
}


std::ostream& operator<<(std::ostream &stream, const InfiniteGame &game) noexcept
{
    stream << game.getUniqueName();
    return stream;
}
