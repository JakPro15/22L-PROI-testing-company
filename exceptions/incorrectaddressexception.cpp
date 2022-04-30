#include "incorrectaddressexception.h"


IncorrectAddressException::IncorrectAddressException(std::string message):
    std::invalid_argument(message){}