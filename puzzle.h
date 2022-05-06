#ifndef PUZZLE_H
#define PUZZLE_H

#include "game.h"


class Puzzle: public Game
{
private:
    // Throws InvalidId if the object's id is invalid for a Puzzle object.
    void checkId() const override;
public:
    enum Difficulty
    {
        Easy=-1,
        Average,
        Difficult,
        VeryDifficult
    };
protected:
    // Returns the unique name of the puzzle (for example "Puzzle 1", if id==20001).
    std::string getUniqueName() const noexcept override;
    // How difficult the puzzle is - on a scale of -1 to 2.
    Difficulty difficulty;
    // How long does it take to complete the game - in minutes.
    unsigned int length;
public:
    // Creates an object of type Puzzle - market price given as a Price object or single int of PLN*100.
    Puzzle(int id, std::string title, Producer &producer, unsigned int filesSize, AbstractGame::Complexity complexity,
           unsigned int minTestersAmount, Difficulty difficulty, unsigned int length, bool codeAvailable=false,
           Price marketPrice=0);
    // Creates an object of type Puzzle - market price given as two ints (zl and gr).
    Puzzle(int id, std::string title, Producer &producer, unsigned int filesSize, AbstractGame::Complexity complexity,
           unsigned int minTestersAmount, Difficulty difficulty, unsigned int length, bool codeAvailable,
           int priceZl, int priceGr);
    // Empty virtual destructor - overwritten from Game.
    ~Puzzle() override;

    // Sets the difficulty of the game.
    void setDifficulty(Difficulty difficulty);
    // Returns the difficulty of the game.
    Difficulty getDifficulty() const noexcept;

    // Sets the length of the game in minutes.
    void setLength(unsigned int length);
    // Returns the length of the game in minutes.
    unsigned int getLength() const noexcept;

    // Returns the expected time to test the game in hours.
    int getTestingTime() const noexcept override;

    // getTestingPrice calculated same as in Game.

    // Compares only the unique IDs of the games.
    bool operator==(const Puzzle &game) const noexcept;
    bool operator!=(const Puzzle &game) const noexcept;

    // Puts the unique name of the game obtained from getUniqueName into the stream.
    friend std::ostream& operator<<(std::ostream &stream, const Puzzle &game);
};


#endif
