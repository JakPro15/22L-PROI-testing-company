#ifndef INVALIDFULLLENGTH_H
#define INVALIDFULLLENGTH_H
#include <stdexcept>


/*
Thrown when attempting to set the length or full length of a game so that full length would be less than length.
*/
class InvalidFullLength: public std::invalid_argument
{
public:
    InvalidFullLength(unsigned  int length, unsigned int fullLength);
};


#endif
