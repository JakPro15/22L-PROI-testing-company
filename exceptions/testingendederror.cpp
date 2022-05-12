#include "testingendederror.h"


TestingEndedError::TestingEndedError():
    std::logic_error("Attempted to modify the record of a finished test.")
{}
