#ifndef GAMENOTPRESENTERROR_H
#define GAMENOTPRESENTERROR_H
#include <stdexcept>


/*
Thrown when attempting to change a game in the producer database when it is not there.
*/
class GameNotPresentError: public std::logic_error
{
public:
    GameNotPresentError();
};


#endif
