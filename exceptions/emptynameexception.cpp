#include "emptynameexception.h"

EmptyNameException::EmptyNameException():
    std::invalid_argument("Name can't be empty"){}

EmptyNameException::EmptyNameException(std::string type):
    std::invalid_argument(type + " name can't be empty"){}