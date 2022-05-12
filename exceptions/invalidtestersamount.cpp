#include "invalidtestersamount.h"


InvalidTestersAmount::InvalidTestersAmount():
    std::invalid_argument("Attempted to set a game's minimal amount of testers to an invalid value.")
{}
