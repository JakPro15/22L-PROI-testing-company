#ifndef TESTINGNOTENDEDERROR_H
#define TESTINGNOTENDEDERROR_H
#include <stdexcept>


/*
Thrown when attempting to modify the record of a fully tested Game.
*/
class TestingNotEndedError: public std::logic_error
{
public:
    TestingNotEndedError();
};


#endif
