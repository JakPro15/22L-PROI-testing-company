#include "conversionerror.h"

ConversionError::ConversionError(std::string string, std::string type):
    std::invalid_argument("String " + string + " could not be converted to " + type){}