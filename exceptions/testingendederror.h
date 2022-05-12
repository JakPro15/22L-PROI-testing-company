#ifndef TESTINGENDEDERROR_H
#define TESTINGENDEDERROR_H
#include <stdexcept>


/*
Thrown when attempting to modify the record of a fully tested Game.
*/
class TestingEndedError: public std::logic_error
{
public:
    TestingEndedError();
};


#endif
