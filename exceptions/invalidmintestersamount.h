#ifndef INVALIDMINTESTERSAMOUNT_H
#define INVALIDMINTESTERSAMOUNT_H
#include <stdexcept>


/*
Thrown when attempting to set a game's minimal amount of testers to an invalid value.
*/
class InvalidMinTestersAmount: public std::invalid_argument
{
public:
    InvalidMinTestersAmount();
};


#endif
