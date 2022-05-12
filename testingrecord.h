#ifndef TESTINGRECORD_H
#define TESTINGRECORD_H
#include "tester.h"
#include "game.h"
#include <list>


class TestingRecord
{
private:
    // Throws InvalidId if the object's id is invalid for a Game object.
    void checkId() const;
    // Unique ID of the game assigned at creation.
    const int id;

    // Reference to the stored Game object.
    const Game &game;
    // List of testers currently testing the game.
    std::list<Tester> testers;
    // Whether the testing is ongoing.
    bool beingTested;
    // Whether the testing has been finished.
    bool testingFinished;
    // Real time it took to test the game (so far).
    unsigned int realTestingTime;
    // Effort needed in total to test the game (1 tester on average produces 5 units of effort per hour).
    unsigned int realTestingEffort;
    // How much effort remains needed to test the game.
    unsigned int effortLeft;
    // How many testers at most should test the game.
    unsigned int maxTestersAmount;

    // Finishes the testing, frees the workers.
    void finalizeTesting() noexcept;
public:
    // These constants define the ID limits for this class.
    const int minId = 6000001;
    const int maxId = 6999999;

    // Creates an object of type TestingRecord storing the given Game.
    TestingRecord(int id, const Game &game, int maxTestersAmount=-1);

    // Returns a const reference to the collection of the game's testers.
    const std::list<Tester>& getTesters() const noexcept;
    // Adds the given tester to the collection of the game's testers.
    void addTester(Tester &tester);
    // Removes the chosen tester from the collection of the game's testers. Does nothing if the tester already isn't there.
    void removeTester(const Tester &tester) noexcept;
    // Returns the current amount of testers.

    // Returns the identifier of the game.
    int getId() const noexcept;

    // Returns a const reference to the game stored by this record.
    const Game& getGame() const noexcept;
    // Returns how many testers at least are needed to test the game.
    unsigned int getMinTestersAmount() const noexcept;

    // Sets how many testers at most should test the game.
    void setMaxTestersAmount(unsigned int maxTestersAmount);
    // Returns how many testers at most should test the game.
    unsigned int getMaxTestersAmount() const noexcept;

    // Advances the testing process by one hour. Returns true if the testing just ended.
    bool advanceTesting();

    // Returns the real time of a finished test in hours
    int getRealTime() const;
    // Returns the real price of a finished test.
    Price getRealPrice() const;
};


#endif
