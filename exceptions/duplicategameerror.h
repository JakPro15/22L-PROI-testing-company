#ifndef DUPLICATEGAMEERROR_H
#define DUPLICATEGAMEERROR_H
#include <stdexcept>


/*
Thrown when attempting to add a game to the producer database that is already there.
*/
class DuplicateGameError: public std::logic_error
{
public:
    DuplicateGameError();
};


#endif
