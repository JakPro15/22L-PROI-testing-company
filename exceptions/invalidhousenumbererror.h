#ifndef INVALIDHOUSENUMBERERROR_H
#define INVALIDHOUSENUMBERERROR_H
#include <stdexcept>


/*
Thrown when the house number given to Address is equal to zero.
*/
class InvalidHouseNumberError: public std::invalid_argument
{
    public:
        InvalidHouseNumberError();
};

#endif
