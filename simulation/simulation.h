#ifndef SIMULATION_H
#define SIMULATION_H

#include "outputhandler.h"


class AbstractGame;

// This class represents the simulation of a testing company

class Simulation
{
    private:
        int current_producer_record_id;
    public:
        // Creates an object of class Simulation
        Simulation();

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
