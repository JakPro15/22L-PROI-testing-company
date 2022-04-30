#ifndef INVALIDFILESSIZE_H
#define INVALIDFILESSIZE_H
#include <stdexcept>


/*
Thrown when attempting to set a game's files' size to an invalid value.
*/
class InvalidFilesSize: public std::invalid_argument
{
public:
    InvalidFilesSize();
};


#endif
