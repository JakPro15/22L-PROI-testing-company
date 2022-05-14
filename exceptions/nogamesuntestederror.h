#ifndef NOGAMESUNTESTEDERROR_H
#define NOGAMESUNTESTEDERROR_H
#include <stdexcept>


/*
Thrown when attempting to get a game to test when none are available.
*/
class NoGamesUntestedError: public std::logic_error
{
public:
    NoGamesUntestedError();
};


#endif
