#ifndef COMPETITIVEGAME_H
#define COMPETITIVEGAME_H

#include "infinitegame.h"


/*
Class representing competitive Player vs Player games, including genres such as First Person Shooter or
Multiplayer Online Battle Arena.
*/
class CompetitiveGame: public InfiniteGame
{
private:
    // Throws InvalidId if the object's id is invalid for a CompetitiveGame object.
    void checkId() const;
protected:
    // Returns the unique name of the game (for example "CompetitiveGame 1", if id==5000001).
    std::string getUniqueName() const noexcept override;
    // How many players at once are expected to be handled by the game server. 0 means the game is to be played via LAN.
    int serverSize;
public:
    // These constants define the ID limits for this class.
    const int minId = 5000001;
    const int maxId = 5999999;

    // Creates an object of type CompetitiveGame - market price given as a Price object or single int of PLN*100.
    CompetitiveGame(int id, std::string title, Producer &producer, unsigned int filesSize, AbstractGame::Complexity complexity,
                    unsigned int minTestersAmount, InfiniteGame::Depth depth, unsigned int serverSize, bool codeAvailable=false,
                    Price marketPrice=0);
    // Creates an object of type CompetitiveGame - market price given as two ints (zl and gr).
    CompetitiveGame(int id, std::string title, Producer &producer, unsigned int filesSize, AbstractGame::Complexity complexity,
                    unsigned int minTestersAmount, InfiniteGame::Depth depth, unsigned int serverSize, bool codeAvailable,
                    int priceZl, int priceGr);
    // Empty virtual destructor - overwritten from InfiniteGame.
    ~CompetitiveGame() override;

    // Sets the expected server size of the game.
    void setServerSize(unsigned int serverSize) noexcept;
    // Returns the expected server size of the game.
    unsigned int getServerSize() const noexcept;

    // Testing time calculated same as in InfiniteGame.

    // Returns the expected price of testing the game.
    Price getTestingPrice() const noexcept override;

    // Compares only the unique IDs of the games.
    bool operator==(const CompetitiveGame &game) const noexcept;
    bool operator!=(const CompetitiveGame &game) const noexcept;

    // Puts the unique name of the game obtained from getUniqueName into the stream.
    friend std::ostream& operator<<(std::ostream &stream, const CompetitiveGame &game) noexcept;
};

#endif
