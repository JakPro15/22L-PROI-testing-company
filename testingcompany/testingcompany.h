#ifndef TESTINGCOMPANY_H
#define TESTINGCOMPANY_H


#include "testingdatabase.h"
#include <iostream>


class AbstractGame;
class AbstractWorker;
class Manager;


class TestingCompany
{
private:
    // Current amount of effort the company can use.
    unsigned int effort;

    // Next request id possible to be given.
    int currentRequestId;

    // Reference to the database of the given company.
    TestingDatabase database;

    // Structure representing record of tested games.
    struct Record
    {
        const AbstractGame& testedGame;
        bool paid;
        // Delay in hours since planned payment time.
        unsigned int delay;
        bool onTime;
    };

    // Collection of records of tested games.
    std::vector<TestingCompany::Record> records;

    // Collection of all pointers to workers working in the company.
    std::vector<std::shared_ptr<AbstractWorker>> workers;

    // Collection of all pointers to testers working in the company.
    std::vector<std::shared_ptr<Tester>> testers;

    // Reference to the output handler.
    OutputHandler& out;

public:
    TestingCompany(OutputHandler& out,
        std::vector<std::shared_ptr<AbstractWorker>> workers,
        std::vector<std::shared_ptr<Tester>> testers);

    // Copying of TestingCompany is forbidden (IDs wouldn't be unique).
    TestingCompany(const TestingCompany&)=delete;
    TestingCompany& operator=(const TestingCompany&)=delete;

    ~TestingCompany() {}

    // Returns the request id and increments the request counter.
    int getRequestId();

    // Adding increases effort held by the company by specified amount.
    void addEffort(unsigned int effort) noexcept;

    // Adds a pointer to tester to workers collection and testers collection.
    void addTester(std::shared_ptr<Tester> tester);

    // Adds a pointer to manager to workers collection.
    void addManager(std::shared_ptr<Manager> manager);

    // Creates a record of the tested game and adds it to tested records
    void testingFinished(const AbstractGame& game);

    // Sets game's record as paid and marks if it was done on time (if not writes down delay).
    void paymentDone(const AbstractGame& game);

    // Adds a new game to the testing database.
    void obtainTestingRequest(const AbstractGame &game);

    // Calling this method signals the Testing Company that one hour has passed.
    void advanceTime();

    bool operator==(const TestingCompany& company) const noexcept;
    bool operator!=(const TestingCompany& company) const noexcept;

    friend std::ostream& operator<<(std::ostream& os, const TestingCompany& company) noexcept;
};


#endif
