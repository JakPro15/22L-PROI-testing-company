#ifndef PRODUCERDATABASE_H
#define PRODUCERDATABASE_H

#include "game.h"
#include "producer.h"
#include <vector>
#include <memory>


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
        Game &game;
        // Whether the testing has been requested.
        bool testingRequested;
        // Whether the testing has finished.
        bool tested;
        // Hours until payment will be done. Ignored if testing not finished.
        unsigned int timeUntilPaid;
        // Creates a record storing the given game.
        Record(int id, Game &game);
    };

    // List of records of the games produced by this producer.
    std::vector<Record> games;
    // Returns the index of the record holding the given Game. Returns -1 if the game is not found.
    int findGame(Game &game);
public:
    // Unique ID of the database assigned at creation.
    const int id;
    // These constants define the ID limits for this class.
    const int minId = 12000001;
    const int maxId = 12999999;

    // Producer this database belongs to.
    Producer &producer;

    // Creates an object of type ProducerDatabase.
    ProducerDatabase(int id, Producer &producer);

    // Adds the given Game to the database. Raises DuplicateGameError if the Game is already there.
    void addGame(Game &game);

    // Advances payment timers and checks whether any games should be paid for.
    void checkPayments();

    // Returns how many games in the database don't have a testing request sent.
    unsigned int getUntestedGamesAmount() const noexcept;
    // Returns a reference to a Game that should be tested. Raises NoGamesUntestedError if there are none.
    Game& getGameToBeTested();

    // Registers in the database that the given game has been tested.
    void gameFinishedTesting(Game& game);
};


#endif
