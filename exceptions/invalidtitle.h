#ifndef INVALIDTITLE_H
#define INVALIDTITLE_H
#include <stdexcept>


/*
Thrown when attempting to set the title of a game to an all-whitespace string.
*/
class InvalidTitle: public std::invalid_argument
{
public:
    InvalidTitle(std::string title);
};


#endif
