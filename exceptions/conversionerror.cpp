#include "conversionerror.h"

ConversionError::ConversionError(std::string string):
    std::invalid_argument("String" + string + "could not be converted to an integer"){}