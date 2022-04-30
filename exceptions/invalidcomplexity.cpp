#include "invalidcomplexity.h"


InvalidComplexity::InvalidComplexity(int complexity):
    std::invalid_argument("Attempted to set a game's complexity to an invalid value: " + std::to_string(complexity))
{}
