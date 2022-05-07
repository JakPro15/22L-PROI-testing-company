#ifndef ROLEPLAYINGGAME_H
#define ROLEPLAYINGGAME_H

#include "game.h"


class RolePlayingGame: public Game
{
private:
    // Throws InvalidId if the object's id is invalid for a RolePlayingGame object.
    void checkId() const;
protected:
    // Returns the unique name of the puzzle (for example "RolePlayingGame 1", if id==3000001).
    std::string getUniqueName() const noexcept override;
    // How long does it take to complete the game - in minutes.
    unsigned int length;
    // How long does it take to fully experience the game - in minutes.
    unsigned int fullLength;
public:
    // These constants define the ID limits for this class.
    const int minId = 3000001;
    const int maxId = 3999999;

    // Creates an object of type RolePlayingGame - market price given as a Price object or single int of PLN*100.
    RolePlayingGame(int id, std::string title, Producer &producer, unsigned int filesSize, AbstractGame::Complexity complexity,
           unsigned int minTestersAmount, int length, int fullLength, bool codeAvailable=false, Price marketPrice=0);
    // Creates an object of type RolePlayingGame - market price given as two ints (zl and gr).
    RolePlayingGame(int id, std::string title, Producer &producer, unsigned int filesSize, AbstractGame::Complexity complexity,
           unsigned int minTestersAmount, int length, int fullLength, bool codeAvailable, int priceZl, int priceGr);
    // Empty virtual destructor - overwritten from Game.
    ~RolePlayingGame() override;

    // Sets the length of the game in minutes.
    void setLength(unsigned int length);
    // Returns the length of the game in minutes.
    unsigned int getLength() const noexcept;

    // Sets the full length of the game in minutes.
    void setFullLength(unsigned int fullLength);
    // Returns the full length of the game in minutes.
    unsigned int getFullLength() const noexcept;

    // Returns the expected time to test the game in hours.
    int getTestingTime() const noexcept override;

    // Returns the expected price of testing the game.
    Price getTestingPrice() const noexcept override;

    // Compares only the unique IDs of the games.
    bool operator==(const RolePlayingGame &game) const noexcept;
    bool operator!=(const RolePlayingGame &game) const noexcept;

    // Puts the unique name of the game obtained from getUniqueName into the stream.
    friend std::ostream& operator<<(std::ostream &stream, const RolePlayingGame &game) noexcept;
};


#endif
