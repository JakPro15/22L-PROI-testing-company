#ifndef PRODUCERDATABASE_H
#define PRODUCERDATABASE_H

#include "../games/abstractgame.h"
#include <vector>
#include <memory>


class AbstractGame;
class Producer;


/*
Class representing a game producer's games database. Stores the information about
testing that Producer has.
*/
class ProducerDatabase
{
private:
    // Throws InvalidId if the object's id is invalid for a TestingDatabase object.
    void checkId() const;

    class Record
    {
    private:
        // Throws InvalidId if the object's id is invalid for a Record object.
        void checkId() const;
    public:
        // Unique ID of the request assigned at creation.
        const int id;
        // These constants define the ID limits for this subclass.
        const int minId = 13000001;
        const int maxId = 13999999;
        // Game stored in this record.
        AbstractGame &game;
        // Whether the testing has been requested.
        bool testingRequested;
        // Whether the testing has finished.
        bool tested;
        // Hours until payment will be done. Ignored if testing not finished.
        unsigned int timeUntilPaid;
        // Creates a record storing the given game.
        Record(int id, AbstractGame &game);
    };

    // List of records of the games produced by this producer.
    std::vector<Record> games;
    // Returns the index of the record holding the given Game. Returns -1 if the game is not found.
    int findGame(AbstractGame &game);
public:
    // Unique ID of the database assigned at creation.
    const int id;
    // These constants define the ID limits for this class.
    static const int minId = 12000001;
    static const int maxId = 12999999;

    // Producer this database belongs to.
    Producer &producer;

    // Creates an object of type ProducerDatabase.
    ProducerDatabase(int id, Producer &producer);

    // Adds the given Game to the database. Raises DuplicateGameError if the Game is already there.
    void addGame(AbstractGame &game);

    // Advances payment timers and checks whether any games should be paid for.
    void checkPayments();

    // Returns how many games in the database don't have a testing request sent.
    unsigned int getUntestedGamesAmount() const noexcept;
    // Returns a reference to a Game that should be tested. Raises NoGamesUntestedError if there are none.
    AbstractGame& getGameToBeTested();

    // Registers in the database that the given game has been tested.
    void gameFinishedTesting(AbstractGame& game);
};


#endif