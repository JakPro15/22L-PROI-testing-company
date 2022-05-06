#include "invalidfulllength.h"


InvalidFullLength::InvalidFullLength(unsigned int length, unsigned int fullLength):
    std::invalid_argument("Attempted to have a game's full length (" + std::to_string(fullLength) + \
        ") be less than its regular length (" +  std::to_string(length) + ")")
{}
