#ifndef PRODUCER_H
#define PRODUCER_H

#include "game.h"


class Game;


class Producer
{
public:
    int getRecordId() { return 13000001; }
    void payForTesting(Game &game) {}
    bool operator==(const Producer &producer) const noexcept {return this == &producer;}
    bool operator!=(const Producer &producer) const noexcept {return not (*this == producer);}
};


#endif
