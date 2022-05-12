#ifndef INVALIDMINTESTERSAMOUNT_H
#define INVALIDMINTESTERSAMOUNT_H
#include <stdexcept>


/*
Thrown when attempting to set a game's minimal amount of testers to an invalid value.
*/
class InvalidTestersAmount: public std::invalid_argument
{
public:
    InvalidTestersAmount();
};


#endif
