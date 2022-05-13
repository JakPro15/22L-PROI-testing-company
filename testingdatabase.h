#ifndef TESTINGDATABASE_H
#define TESTINGDATABASE_H

#include "testingrecord.h"
#include "testingcompany.h"
#include <vector>
#include <deque>
#include <queue>
#include <list>
#include <memory>


class TestingCompany;


class TestingDatabase
{
private:
    // Throws InvalidId if the object's id is invalid for a TestingDatabase object.
    void checkId() const;
    // Unique ID of the database assigned at creation.
    const int id;

    // Reference to the company this database belongs to.
    TestingCompany &company;

    // Represents a not yet processed testing request.
    class Request
    {
    private:
        // Throws InvalidId if the object's id is invalid for a Request object.
        void checkId() const;
        // Unique ID of the request assigned at creation.
        const int id;
    public:
        const int minId = 11000001;
        const int maxId = 11999999;
        const int effortPerRequest = 20;
        const Game &game;
        unsigned int effortLeft;
        Request(int id, const Game &game);
        int getId() const noexcept;
    };

    // Queue of requests waiting to be processed.
    std::queue<Request> testingRequests;
    // Double ended queue of games waiting to being testing.
    std::deque<std::unique_ptr<TestingRecord>> gamesNotBeingTested;
    // List of games currently being tested.
    std::list<std::unique_ptr<TestingRecord>> gamesBeingTested;
public:
    // These constants define the ID limits for this class.
    const int minId = 7000001;
    const int maxId = 7999999;

     // Creates an object of type TestingDatabase within the given TestingCompany.
    TestingDatabase(int id, TestingCompany &company);

    // Returns the identifier of the database.
    int getId() const noexcept;

    // Returns the company this database belongs to.
    TestingCompany& getCompany() const noexcept;

    // These functions return the sizes of their respective collections.
    unsigned int getGamesBeingTestedAmount() const noexcept;
    unsigned int getGamesWaitingForTestersAmount() const noexcept;
    unsigned int getTestRequestsAmount() const noexcept;

    // Adds a new request to the queue with the given Game.
    void newTestingRequest(const Game &game);
    // Advances the handling of the first request in the queue by the given amount.
    void advanceRequestHandling(unsigned int effortPut) noexcept;

    // Calls time advancement and finish checks on all records.
    void checkRecords();
    // Assigns the tester to a game and returns true. If there are no available games, returns false.
    bool assignTester(std::shared_ptr<Tester> tester);
};


#endif
