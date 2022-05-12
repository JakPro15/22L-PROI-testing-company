#include "testingnotendederror.h"


TestingNotEndedError::TestingNotEndedError():
    std::logic_error("Attempted to obtain the real time or price of an unfinished test.")
{}
