#ifndef PRODUCER_H
#define PRODUCER_H

#include "../games/abstractgame.h"


class AbstractGame;


/*
Class representing companies that produce games and request testing of games.
*/
class Producer
{
public:
    int getRecordId() { return 13000001; }
    void payForTesting(AbstractGame &game) {}
    bool operator==(const Producer &producer) const noexcept {return this == &producer;}
    bool operator!=(const Producer &producer) const noexcept {return not (*this == producer);}
};


#endif
