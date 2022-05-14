#ifndef GAMEALREADYTESTEDERROR_H
#define GAMEALREADYTESTEDERROR_H
#include <stdexcept>


/*
Thrown when attempting to set an already tested game to tested.
*/
class GameAlreadyTestedError: public std::logic_error
{
public:
    GameAlreadyTestedError();
};


#endif
