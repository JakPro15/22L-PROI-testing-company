#ifndef _SIMULATION_H
#define _SIMULATION_H

#include "outputhandler.h"
#include "inputfilehandler.h"
#include "../testingcompany/testingcompany.h"


class AbstractGame;

// This class represents the simulation of a testing company.

class Simulation
{
    private:

        //Object of class handling the outputs of the simulation
        OutputHandler out;

        // Object of class handling the inputs to the simulation.
        InputFileHandler in;

        // The next id which may be given to a producer record.
        int currentProducerRecordId;

        // Number of testers in the simulation.
        unsigned int testersAmount;

        // Number of managers in the simulation.
        unsigned int managersAmount;

        // Testing company whose work is being simulated.
        TestingCompany testingCompany;

        // Vector of shared pointers to producers
        std::vector<std::shared_ptr<Producer>> producers;

        // Vector of shared pointers to games
        std::vector<std::shared_ptr<AbstractGame>> games;

    public:
        // Creates an object of class Simulation
        Simulation(
            unsigned int testersAmount, unsigned int managersAmount,
            std::string producersFileName, std::string gamesFileName,
            std::string testersFileName, std::string managersFileName,
            std::string outFileName);

        // Activates the simulation for a given number of iterations.
        void simulate(unsigned int iterations);

        // Returns a reference to the testing company whose work is being simulated.
        TestingCompany& getTestingCompany() noexcept;

        // Returns current id a producer would have and increments it to keep id's unique.
        int getProducerRecordId();

        // Returns a reference to a game taken from the input file.
        AbstractGame& getNewGame(Producer& producer);

        // Compares two Simulation objects.
        bool operator==(const Simulation &simulation) const noexcept;
        bool operator!=(const Simulation &simulation) const noexcept;

        // Inputs a string representation of an Simulation object into the stream
        friend std::ostream& operator<<(std::ostream& os, const Simulation& simulation) noexcept;
};


#endif
