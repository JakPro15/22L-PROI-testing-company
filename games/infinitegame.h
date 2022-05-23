#ifndef INFINITEGAME_H
#define INFINITEGAME_H

#include "game.h"


/*
Class representing games with infinite replayability, single- or multiplayer.
*/
class InfiniteGame: public Game
{
private:
    // Throws InvalidId if the object's id is invalid for an InfiniteGame object.
    void checkId() const;
public:
    enum Depth
    {
        Shallow=-1,
        Average,
        Deep,
        Expansive
    };
protected:
    // Returns the unique name of the game (for example "InfiniteGame 1", if id==4000001).
    std::string getUniqueName() const noexcept override;
    // Score of how much content there is in the game - from -1 to 2
    Depth depth;

    // Protected constructor that doesn't check ID - used in derived classes with different ID sets.
    // First argument (char) used only to differentiate from other constructors.
    InfiniteGame(char, int id, std::string title, Producer &producer, unsigned int filesSize,
                 AbstractGame::Complexity complexity, unsigned int minTestersAmount, Depth depth, bool codeAvailable=false,
                 Price marketPrice=0);
public:
    // These constants define the ID limits for this class.
    static const int minId = 4000001;
    static const int maxId = 4999999;

    // Creates an object of type InfiniteGame - market price given as a Price object or single int of PLN*100.
    InfiniteGame(int id, std::string title, Producer &producer, unsigned int filesSize, AbstractGame::Complexity complexity,
                 unsigned int minTestersAmount, Depth depth, bool codeAvailable=false, Price marketPrice=0);
    // Creates an object of type InfiniteGame - market price given as two ints (zl and gr).
    InfiniteGame(int id, std::string title, Producer &producer, unsigned int filesSize, AbstractGame::Complexity complexity,
                 unsigned int minTestersAmount, Depth depth, bool codeAvailable, int priceZl, int priceGr);

    // Copying of InfiniteGame is forbidden (IDs wouldn't be unique).
    InfiniteGame(const InfiniteGame&)=delete;
    InfiniteGame& operator=(const InfiniteGame&)=delete;

    // Empty virtual destructor - overwritten from Game.
    ~InfiniteGame() override;

    // Sets the depth of the game.
    void setDepth(Depth depth) noexcept;
    // Returns the depth of the game.
    Depth getDepth() const noexcept;

    // Returns the expected time to test the game in hours.
    int getTestingTime() const noexcept override;

    // getTestingPrice calculated same as in Game.

    // Compares only the unique IDs of the games.
    bool operator==(const InfiniteGame &game) const noexcept;
    bool operator!=(const InfiniteGame &game) const noexcept;

    // Puts the unique name of the game obtained from getUniqueName into the stream.
    friend std::ostream& operator<<(std::ostream &stream, const InfiniteGame &game) noexcept;
};

#endif
