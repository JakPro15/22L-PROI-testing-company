#ifndef SIMULATION_H
#define SIMULATION_H

#include "../games/game.h"
#include "../testingcompany/testingcompany.h"


class Simulation
{
public:
    int getProducerRecordId() { return 13000001; }
    AbstractGame& getNewGame() {}
    bool operator==(const Simulation &simulation) const noexcept { return this == &simulation; }
    bool operator!=(const Simulation &simulation) const noexcept { return not (*this == simulation); };
};


#endif
