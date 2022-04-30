#include "zeroexception.h"

ZeroException::ZeroException(std::string numberCategory):
    std::invalid_argument(numberCategory + " can't be equal to zero"){}