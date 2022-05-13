#ifndef _PRODUCTIVITY_OUT_OF_RANGE_EXCEPTION_H
#define _PRODUCTIVITY_OUT_OF_RANGE_EXCEPTION_H
#include <stdexcept>


/*
Thrown when productivity exceeds the range from 1 to 9.
*/
class ProductivityOutOfRangeException: public std::invalid_argument 
{
    public:
        ProductivityOutOfRangeException();
};
#endif