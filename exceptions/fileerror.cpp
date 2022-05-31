#include "fileerror.h"

FileError::FileError(std::string fileName):
    std::invalid_argument("File " + fileName + " could not be opened"){}

FileError::FileError(char c, std::string msg):
    std::invalid_argument(msg){}