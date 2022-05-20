#include "../puzzle.h"
#include "../../exceptions.h"
#include <cmath>


void Puzzle::checkId() const
{
    if(id < minId or id > maxId)
    {
        throw InvalidId("Puzzle", id);
    }
}


std::string Puzzle::getUniqueName() const noexcept
{
    return "Puzzle " + std::to_string(id - minId + 1);
}


Puzzle::Puzzle(int id, std::string title, Producer &producer, unsigned int filesSize, AbstractGame::Complexity complexity,
               unsigned int minTestersAmount, Difficulty difficulty, unsigned int length, bool codeAvailable,
               Price marketPrice):
    Game('a', id, title, producer, filesSize, complexity, minTestersAmount, codeAvailable, marketPrice),
    difficulty(difficulty), length(length)
{
    checkId();  // Different checkId than the one in Game::Game regular (public) constructor
    if(length == 0)
    {
        throw InvalidLength();
    }
}


Puzzle::Puzzle(int id, std::string title, Producer &producer, unsigned int filesSize, AbstractGame::Complexity complexity,
               unsigned int minTestersAmount, Difficulty difficulty, unsigned int length, bool codeAvailable,
               int priceZl, int priceGr):
    Puzzle(id, title, producer, filesSize, complexity, minTestersAmount, difficulty, length, codeAvailable,
           Price(priceZl, priceGr))
{}


Puzzle::~Puzzle()
{}


void Puzzle::setDifficulty(Difficulty difficulty) noexcept
{
    this->difficulty = difficulty;
}


Puzzle::Difficulty Puzzle::getDifficulty() const noexcept
{
    return difficulty;
}


void Puzzle::setLength(unsigned int length)
{
    if(length == 0)
    {
        throw InvalidLength();
    }
    else
    {
        this->length = length;
    }
}


unsigned int Puzzle::getLength() const noexcept
{
    return length;
}


int Puzzle::getTestingTime() const noexcept
{
    // Estimated time: 2x the time to complete the game + an hour per 5 MB of game files
    double testingTime = length / 30 + filesSize / 5000;
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
    // Time modified similarly by difficulty.
    testingTime *= (1 + 0.2 * difficulty);
    // Time increased further by 20% if many testers are needed at once.
    if(minTestersAmount > 10)
    {
        testingTime *= 1.2;
    }
    return ceil(testingTime);
}


bool Puzzle::operator==(const Puzzle &game) const noexcept
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


bool Puzzle::operator!=(const Puzzle &game) const noexcept
{
    return not (*this == game);
}


std::ostream& operator<<(std::ostream &stream, const Puzzle &game) noexcept
{
    stream << game.getUniqueName();
    return stream;
}
