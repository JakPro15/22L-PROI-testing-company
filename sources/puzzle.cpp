#include "../puzzle.h"
#include "../exceptions.h"
#include <cmath>


void Puzzle::checkId() const
{
    if(id < 20001 or id > 29999)
    {
        throw InvalidId("Puzzle", id);
    }
}


std::string Puzzle::getUniqueName() const noexcept
{
    return "Puzzle " + std::to_string(id - 20000);
}


Puzzle::Puzzle(int id, std::string title, Producer &producer, unsigned int filesSize, AbstractGame::Complexity complexity,
               unsigned int minTestersAmount, Difficulty difficulty, bool codeAvailable, Price marketPrice):
               Game('a', id, title, producer, filesSize, complexity, minTestersAmount, codeAvailable, marketPrice),
               difficulty(difficulty)
{
    checkId();  // Different checkId than the one in Game::Game
}


Puzzle::Puzzle(int id, std::string title, Producer &producer, unsigned int filesSize, AbstractGame::Complexity complexity,
               unsigned int minTestersAmount, Difficulty difficulty, bool codeAvailable, int priceZl, int priceGr):
               Puzzle(id, title, producer, filesSize, complexity, minTestersAmount, difficulty, codeAvailable,
                      Price(priceZl, priceGr))
{}


Puzzle::~Puzzle()
{}


void Puzzle::setDifficulty(Difficulty difficulty)
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
    if(complexity > 0)
    {
        testingTime *= (1 + 0.2 * difficulty);
    }
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


std::ostream& operator<<(std::ostream &stream, const Puzzle &game)
{
    stream << game.getUniqueName();
    return stream;
}
