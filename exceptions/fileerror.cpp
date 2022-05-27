#include "fileerror.h"

FileError::FileError():
    std::invalid_argument("File could not be opened"){}