#include "invalidlength.h"


InvalidLength::InvalidLength():
    std::invalid_argument("Attempted to set the game's length to zero.")
{}
