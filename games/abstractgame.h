#ifndef ABSTRACTGAME_H
#define ABSTRACTGAME_H

#include "price.h"
#include <string>


class Producer;


/*
Abstract Game class defining the interface for all games in the simulation.
*/
class AbstractGame
{
public:
    enum Complexity
    {
        Simple=0,
        Average,
        Complex
    };

    // Empty virtual destructor - for inheritance.
    virtual ~AbstractGame() {};

    // Returns the identifier of the game.
    virtual int getId() const noexcept=0;

    // Sets the title of the game. Empty (all whitespace) titles are not allowed.
    virtual void setTitle(std::string title)=0;
    // Returns the title of the game.
    virtual std::string getTitle() const noexcept=0;

    // Sets the size of the game's files in kB.
    virtual void setFilesSize(unsigned int filesSize)=0;
    // Returns the size of the game's files in kB.
    virtual unsigned int getFilesSize() const noexcept=0;

    // Sets the availability of the game's source code.
    virtual void setCodeAvailable(bool codeAvailable) noexcept=0;
    // Returns whether the game's source code is available to the testers.
    virtual unsigned int getCodeAvailable() const noexcept=0;

    // Sets the price of the game (for users).
    virtual void setMarketPrice(Price marketPrice)=0;
    virtual void setMarketPrice(int priceZl, int priceGr)=0;
    // Returns the price of the game (for users).
    virtual Price getMarketPrice() const noexcept=0;

    // Sets the complexity of the game.
    virtual void setComplexity(Complexity complexity)=0;
    // Returns how complex the game is.
    virtual Complexity getComplexity() const noexcept=0;

    // Returns the company that commissioned the testing.
    virtual Producer& getProducer() const noexcept=0;

    // Returns at least how many testers the game needs at a given moment.
    virtual void setMinTestersAmount(unsigned int minTestersAmount)=0;
    // Returns at least how many testers the game needs at a given moment.
    virtual unsigned int getMinTestersAmount() const noexcept=0;

    // Returns the expected time to test the game.
    virtual int getTestingTime() const noexcept=0;

    // Returns the expected price of testing the game.
    virtual Price getTestingPrice() const noexcept=0;

    // Compares the given games.
    virtual bool operator==(const AbstractGame &game) const noexcept=0;
    virtual bool operator!=(const AbstractGame &game) const noexcept=0;
};


#endif
