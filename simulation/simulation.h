#ifndef _SIMULATION_H
#define _SIMULATION_H

#include "outputhandler.h"
#include "../testingcompany/testingcompany.h"


class AbstractGame;

// This class represents the simulation of a testing company.

class Simulation
{
    private:
        // Testing company whose work is being simulated.
        TestingCompany testingCompany;

        // The next id which may be given to a producer record.
        int currentProducerRecordId;

        // Number of iterations through which the simulation will go.
        unsigned int iterations;

        // Number of testers in the simulation.
        unsigned int testersAmount;

        // Number of managers in the simulation.
        unsigned int managersAmount;

    public:
        // Creates an object of class Simulation
        Simulation(unsigned int iterations, unsigned int testersAmount, unsigned int managersAmount);

        // Returns a reference to the testing company whose work is being simulated.
        TestingCompany& getTestingCompany() noexcept;

        // Returns current id a producer would have and increments it to keep id's unique.
        int getProducerRecordId();

        // Returns a reference to a game taken from the input file.
        AbstractGame& getNewGame() {}

        // Compares two Simulation objects.
        bool operator==(const Simulation &simulation) const noexcept;
        bool operator!=(const Simulation &simulation) const noexcept;

        // Inputs a string representation of an Simulation object into the stream
        friend std::ostream& operator<<(std::ostream& os, const Simulation& simulation) noexcept;
};


#endif
