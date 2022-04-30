#ifndef _EMPTYNAMEEXCEPTION_H
#define _EMPTYNAMEEXCEPTION_H
#include <stdexcept>


/*
Thrown when name contains only whitespaces
when it's not supposed to.
*/
class EmptyNameException: public std::invalid_argument 
{
    public:
        EmptyNameException(std::string type);
        EmptyNameException();
};
#endif