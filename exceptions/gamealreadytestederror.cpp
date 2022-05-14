#include "gamealreadytestederror.h"


GameAlreadyTestedError::GameAlreadyTestedError():
    std::logic_error("Attempted to to set an already tested game to tested.")
{}
