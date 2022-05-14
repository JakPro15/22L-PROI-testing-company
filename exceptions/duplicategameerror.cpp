#include "duplicategameerror.h"


DuplicateGameError::DuplicateGameError():
    std::logic_error("Attempted to add a game to ProducerDatabase that is already there.")
{}
