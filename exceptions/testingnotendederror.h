#ifndef TESTINGNOTENDEDERROR_H
#define TESTINGNOTENDEDERROR_H
#include <stdexcept>


/*
Thrown when attempting to obtain the final parameters of a not fully tested game from testing record.
*/
class TestingNotEndedError: public std::logic_error
{
public:
    TestingNotEndedError();
};


#endif
