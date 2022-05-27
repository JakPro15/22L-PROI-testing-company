#include "fileerror.h"

FileError::FileError(std::string fileName):
    std::invalid_argument("File " + fileName + "could not be opened"){}