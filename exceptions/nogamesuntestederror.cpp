#include "nogamesuntestederror.h"


NoGamesUntestedError::NoGamesUntestedError():
    std::logic_error("Attempted to get a game to test when none are available.")
{}
