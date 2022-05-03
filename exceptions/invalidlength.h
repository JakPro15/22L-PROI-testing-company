#ifndef INVALIDLENGTH_H
#define INVALIDLENGTH_H
#include <stdexcept>


/*
Thrown when attempting to set the length of a game to zero.
*/
class InvalidLength: public std::invalid_argument
{
public:
    InvalidLength();
};


#endif
