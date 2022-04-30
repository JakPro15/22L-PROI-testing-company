#ifndef INVALIDID_H
#define INVALIDID_H
#include <stdexcept>


/*
Thrown when attempting to set an id to a value not valid for the object.
*/
class InvalidId: public std::invalid_argument
{
public:
    InvalidId(std::string typeName, int id);
};


#endif
