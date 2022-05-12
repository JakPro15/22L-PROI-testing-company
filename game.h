#ifndef GAME_H
#define GAME_H

#include "abstractgame.h"
#include <iostream>


class Game: public AbstractGame
{
private:
    // Throws InvalidId if the object's id is invalid for a Game object.
    void checkId() const;
protected:
    // Returns the unique name of the game (for example "Game 1", if id==1000001).
    virtual std::string getUniqueName() const noexcept;
    // Unique ID of the game assigned at creation.
    const int id;
    // Title of the game. Cannot be all-whitespace.
    std::string title;
    // Reference to the company that commissioned the testing.
    Producer &producer;
    // Size of the game's files in kilobytes.
    unsigned int filesSize;
    // Complexity of the game (on a scale from 0 to 3).
    AbstractGame::Complexity complexity;
    // At least how many testers are needed to test the game.
    unsigned int minTestersAmount;
    // Whether the game's code is available to the testers.
    bool codeAvailable;
    // Price of the game (for users).
    Price marketPrice;
    // Protected constructor that doesn't check ID - used in derived classes with different ID sets.
    // First argument (char) used only to differentiate from other constructors.
    Game(char, int id, std::string title, Producer &producer, unsigned int filesSize, AbstractGame::Complexity complexity,
         unsigned int minTestersAmount, bool codeAvailable=false, Price marketPrice=0);
public:
    // These constants define the ID limits for this class.
    const int minId = 1000001;
    const int maxId = 1999999;

    // Creates an object of type Game - market price given as a Price object or single int of PLN*100.
    Game(int id, std::string title, Producer &producer, unsigned int filesSize, AbstractGame::Complexity complexity,
         unsigned int minTestersAmount, bool codeAvailable=false, Price marketPrice=0);
    // Creates an object of type Game - market price given as two ints (zl and gr).
    Game(int id, std::string title, Producer &producer, unsigned int filesSize, AbstractGame::Complexity complexity,
         unsigned int minTestersAmount, bool codeAvailable, int priceZl, int priceGr);
    // Empty virtual destructor - for inheritance.
    ~Game() override;

    // Returns the identifier of the game.
    int getId() const noexcept override;

    // Sets the title of the game. Empty (all whitespace) titles are not allowed.
    void setTitle(std::string title) override;
    // Returns the title of the game.
    std::string getTitle() const noexcept override;

    // Sets the size of the game's files in kB.
    void setFilesSize(unsigned int filesSize) override;
    // Returns the size of the game's files in kB.
    unsigned int getFilesSize() const noexcept override;

    // Sets the availability of the game's source code.
    void setCodeAvailable(bool codeAvailable) noexcept override;
    // Returns whether the game's source code is available to the testers.
    unsigned int getCodeAvailable() const noexcept override;

    // Sets the price of the game (for users).
    void setMarketPrice(Price marketPrice) override;
    void setMarketPrice(int priceZl, int priceGr) override;
    // Returns the price of the game (for users).
    Price getMarketPrice() const noexcept override;

    // Sets the complexity of the game.
    void setComplexity(AbstractGame::Complexity complexity) override;
    // Returns how complex the game is.
    AbstractGame::Complexity getComplexity() const noexcept override;

    // Returns the company that commissioned the testing.
    Producer& getProducer() const noexcept override;

    // Returns at least how many testers the game needs at a given moment.
    void setMinTestersAmount(unsigned int minTestersAmount) override;
    // Returns at least how many testers the game needs at a given moment.
    unsigned int getMinTestersAmount() const noexcept override;

    // Returns the expected time to test the game in hours.
    int getTestingTime() const noexcept override;

    // Returns the expected price of testing the game.
    Price getTestingPrice() const noexcept override;

    // Compares only the unique IDs of the games.
    bool operator==(const Game &game) const noexcept;
    bool operator!=(const Game &game) const noexcept;

    // Puts the unique name of the game obtained from getUniqueName into the stream.
    friend std::ostream& operator<<(std::ostream &stream, const Game &game) noexcept;
};

#endif
