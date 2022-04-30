#include "invalidfilessize.h"


InvalidFilesSize::InvalidFilesSize():
    std::invalid_argument("Attempted to set a game's files' size to zero.")
{}
