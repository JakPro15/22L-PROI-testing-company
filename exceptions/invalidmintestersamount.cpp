#include "invalidmintestersamount.h"


InvalidMinTestersAmount::InvalidMinTestersAmount():
    std::invalid_argument("Attempted to set a game's minimal amount of testers to zero.")
{}
