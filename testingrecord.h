#include "tester.h"
#include <list>


class TestingRecord
{
public:
    TestingRecord(/* args */);
    ~TestingRecord();
    // Returns a const reference to the collection of the game's testers.
    virtual const std::list<Tester>& getTesters() const noexcept;
    // Adds the given tester to the collection of testers.
    virtual void addTester(Tester &tester);
    // Removes the chosen tester from the collection of the game's testers. Does nothing if the tester already isn't there.
    virtual void removeTester(const Tester &tester) noexcept;
};
