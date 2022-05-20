#ifndef PRODUCER_H
#define PRODUCER_H

#include "../games/abstractgame.h"
#include "../testingcompany/address.h"
#include "../testingcompany/testingcompany.h"
#include "../simulation/simulation.h"
#include "producerdatabase.h"
#include <string>


class AbstractGame;
class TestingCompany;


/*
Class representing a company that produces games and requests testing of games.
*/
class Producer
{
private:
    // Throws InvalidId if the object's id is invalid for a Producer object.
    void checkId() const;

    // Official name of the company.
    std::string name;
    // Address of the main headquarters of the company.
    Address address;

    // The producer's database of games and their testing information.
    ProducerDatabase database;
public:
    // Unique ID of the producer assigned at creation.
    const int id;
    // These constants define the ID limits for this class.
    static const int minId = 14000001;
    static const int maxId = 14999999;

    // Simulation this producer is part of.
    Simulation &simulation;

    // Testing company providing testing of games to this producer.
    TestingCompany &testingCompany;

    // Creates an object of class Producer.
    Producer(int id, std::string name, Address address, Simulation &simulation, TestingCompany &testingCompany);

    // Copying of Producer is forbidden (IDs wouldn't be unique).
    Producer(const Producer&)=delete;
    Producer& operator=(const Producer&)=delete;

    // Sets the name of the producer. Empty (all whitespace) names are not allowed.
    void setName(std::string name);
    // Returns the name of the producer.
    std::string getName() const noexcept;

    // Sets the address of the producer.
    void setAddress(Address address) noexcept;
    // Returns the address of the producer.
    Address getAddress() const noexcept;

    // Returns an id for a producer's game record obtained from Simulation.
    int getRecordId() noexcept;

    // Sends information to the TestingCompany that the testing of the given game has been paid for.
    void payForTesting(AbstractGame &game);

    // Calling this function signals to the Producer that one hour has passed.
    void advanceTime();

    // Compares only the unique IDs of the producers.
    bool operator==(const Producer &producer) const noexcept;
    bool operator!=(const Producer &producer) const noexcept;

    // Puts the unique name of the producer obtained from getUniqueName into the stream.
    friend std::ostream& operator<<(std::ostream &stream, const Producer &producer) noexcept;
};


#endif