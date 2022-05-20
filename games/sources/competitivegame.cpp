#include "../competitivegame.h"
#include "../../exceptions.h"
#include <cmath>


void CompetitiveGame::checkId() const
{
    if(id < minId or id > maxId)
    {
        throw InvalidId("CompetitiveGame", id);
    }
}


std::string CompetitiveGame::getUniqueName() const noexcept
{
    return "CompetitiveGame " + std::to_string(id - minId + 1);
}


CompetitiveGame::CompetitiveGame(int id, std::string title, Producer &producer, unsigned int filesSize,
                                 AbstractGame::Complexity complexity, unsigned int minTestersAmount, InfiniteGame::Depth depth,
                                 unsigned int serverSize, bool codeAvailable, Price marketPrice):
    InfiniteGame('a', id, title, producer, filesSize, complexity, minTestersAmount, depth, codeAvailable, marketPrice),
    serverSize(serverSize)
{
    checkId();  // Different checkId than the one in InfiniteGame::InfiniteGame regular (public) constructor
}


CompetitiveGame::CompetitiveGame(int id, std::string title, Producer &producer, unsigned int filesSize,
                                 AbstractGame::Complexity complexity, unsigned int minTestersAmount, InfiniteGame::Depth depth,
                                 unsigned int serverSize, bool codeAvailable, int priceZl, int priceGr):
    CompetitiveGame(id, title, producer, filesSize, complexity, minTestersAmount, depth, serverSize, codeAvailable,
                    Price(priceZl, priceGr))
{}


CompetitiveGame::~CompetitiveGame()
{}


void CompetitiveGame::setServerSize(unsigned int serverSize) noexcept
{
    this->serverSize = serverSize;
}


unsigned int CompetitiveGame::getServerSize() const noexcept
{
    return serverSize;
}


Price CompetitiveGame::getTestingPrice() const noexcept
{
    Price testingPrice = InfiniteGame::getTestingPrice();
    // Difference from InfiniteGame class: more expensive testing if many players need to be handled at once by the server.
    // 1% price increase per 10 players handled simultaneously by the server.
    testingPrice *= (1 + serverSize * 0.001);
    return testingPrice;
}


bool CompetitiveGame::operator==(const CompetitiveGame &game) const noexcept
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


bool CompetitiveGame::operator!=(const CompetitiveGame &game) const noexcept
{
    return not (*this == game);
}


std::ostream& operator<<(std::ostream &stream, const CompetitiveGame &game) noexcept
{
    stream << game.getUniqueName();
    return stream;
}
