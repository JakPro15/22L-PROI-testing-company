#ifndef INVALIDPRODUCER_H
#define INVALIDPRODUCER_H
#include <stdexcept>


/*
Thrown when attempting to add a game that was produced by a different company to a producer's database.
*/
class InvalidProducer: public std::invalid_argument
{
public:
    InvalidProducer();
};


#endif
