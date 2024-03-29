#ifndef TESTINGCOMPANY_H
#define TESTINGCOMPANY_H

#include "testingdatabase.h"
#include "../games/price.h"
#include <iostream>


class AbstractGame;
class AbstractWorker;
class Manager;


class TestingCompany
{
public:
    // Unique ID of the company assigned at creation.
    const int id;

    // Structure representing record of tested games.
    class Record
    {
        private:
            // Throws InvalidId if the object's id is invalid for a Record object.
            void checkId() const;
        public:
            // These constants define the ID limits for this class.
            static const int minId = 16000001;
            static const int maxId = 16999999;

            // Creates a record with paid = false, delay = 0 and onTime = true.
            Record(int id, const AbstractGame& testedGame, Price price);

            // Unique ID of the record assigned at creation.
            const int id;

            const AbstractGame& testedGame;
            Price testingPrice;
            bool paid;
            // Delay in hours since planned payment time.
            unsigned int delay;
            bool onTime;
    };
private:
    // Current amount of effort the company can use.
    unsigned int effort;

    // Next request id possible to be given.
    int currentRequestId;

    // Next record id possible to be given.
    int currentRecordId;

    // Reference to the database of the given company.
    TestingDatabase database;

    // Collection of records of tested games.
    std::vector<TestingCompany::Record> records;

    // Collection of all pointers to workers working in the company.
    std::vector<std::shared_ptr<AbstractWorker>> workers;

    // Collection of all pointers to testers working in the company.
    std::vector<std::shared_ptr<Tester>> testers;

    // Reference to the output handler.
    OutputHandler& out;

    // Throws InvalidId if the object's id is invalid for a TestingCompany object.
    void checkId() const;

public:
    // These constants define the ID limits for this class.
    static const int minId = 15000001;
    static const int maxId = 15999999;

    TestingCompany(int id, OutputHandler& out,
        std::vector<std::shared_ptr<AbstractWorker>> workers = {},
        std::vector<std::shared_ptr<Tester>> testers = {});

    // Copying of TestingCompany is forbidden (IDs wouldn't be unique).
    TestingCompany(const TestingCompany&)=delete;
    TestingCompany& operator=(const TestingCompany&)=delete;

    // Returns the request id and increments the request counter.
    int getRequestId();

    // Returns current effort the company holds.
    unsigned int getEffort() const noexcept;

    // Returns the amount of records in the company.
    int getRecords() const noexcept;

    // Returns the amount of workers in the company.
    int getWorkers() const noexcept;

    // Returns the amount of testers in the company.
    int getTesters() const noexcept;

    // Returns a copy of records held by the company.
    const std::vector<TestingCompany::Record>& showRecords() const noexcept;

    // Adding increases effort held by the company by specified amount.
    void addEffort(unsigned int effort) noexcept;

    // Adds a pointer to tester to workers collection and testers collection.
    void addTester(std::shared_ptr<Tester> tester);

    // Adds a pointer to manager to workers collection.
    void addManager(std::shared_ptr<Manager> manager);

    // Creates a record of the tested game and adds it to tested records
    void testingFinished(const AbstractGame& game, Price price);

    // Sets game's record as paid and marks if it was done on time (if not writes down delay).
    void paymentDone(const AbstractGame& game);

    // Adds a new game to the testing database.
    void obtainTestingRequest(const AbstractGame &game);

    // Calling this method signals the Testing Company that one hour has passed.
    void advanceTime();

    // Returns whether there is any work for managers to do.
    bool isThereWork() const noexcept;

    bool operator==(const TestingCompany& company) const noexcept;
    bool operator!=(const TestingCompany& company) const noexcept;

    friend std::ostream& operator<<(std::ostream& os, const TestingCompany& company) noexcept;
};


#endif
