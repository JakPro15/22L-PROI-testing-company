#ifndef INVALIDCOMPLEXITY_H
#define INVALIDCOMPLEXITY_H
#include <stdexcept>


/*
Thrown when attempting to set a game's complexity to an invalid value.
*/
class InvalidComplexity: public std::invalid_argument
{
public:
    InvalidComplexity(int complexity);
};


#endif
