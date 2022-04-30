#ifndef _ZERO_EXCEPTION_H
#define _ZERO_EXCEPTION_H
#include <stdexcept>


/*
Thrown when a value is equal to zero
when it's not supposed to.
*/
class ZeroException: public std::invalid_argument 
{
    public:
        ZeroException(std::string numberCategory);
};
#endif