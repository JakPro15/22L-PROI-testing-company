#ifndef _INCORRECTADDRESSEXCEPTION_H
#define _INCORRECTADDRESSEXCEPTION_H
#include <stdexcept>


/*
Thrown when address isn't of the format dd-ddd (d stands for digit)
*/
class IncorrectAddressException: public std::invalid_argument 
{
    public:
        IncorrectAddressException(std::string message);
};
#endif