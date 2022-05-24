#ifndef SIMULATION_H
#define SIMULATION_H

#include "outputhandler.h"


class AbstractGame;


class Simulation
{
public:
    int getProducerRecordId() { return 13000001; }
    AbstractGame& getNewGame();
    bool operator==(const Simulation &simulation) const noexcept { return this == &simulation; }
    bool operator!=(const Simulation &simulation) const noexcept { return not (*this == simulation); };
    friend std::ostream& operator<<(std::ostream &stream, const Simulation &simulation) noexcept { return stream; }
};


#endif
