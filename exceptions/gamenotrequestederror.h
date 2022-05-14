#ifndef GAMENOTREQUESTEDERROR_H
#define GAMENOTREQUESTEDERROR_H
#include <stdexcept>


/*
Thrown when attempting to set a game as tested when its testing hadn't been requested.
*/
class GameNotRequestedError: public std::logic_error
{
public:
    GameNotRequestedError();
};


#endif
