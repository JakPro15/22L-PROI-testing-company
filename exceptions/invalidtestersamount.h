#ifndef INVALIDMINTESTERSAMOUNT_H
#define INVALIDMINTESTERSAMOUNT_H
#include <stdexcept>


/*
Thrown when attempting to set a game's minimal amount of testers to an invalid value
or when trying to set a game's maximal amount of testers to be lower than minimal amount of testers.
*/
class InvalidTestersAmount: public std::invalid_argument
{
public:
    InvalidTestersAmount();
};


#endif
