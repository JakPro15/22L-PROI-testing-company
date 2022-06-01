#ifndef _CONVERSIONERROR_H
#define _CONVERSIONERROR_H

// Thrown when a conversion to specified type couldn't go through.

#include <stdexcept>

class ConversionError: public std::invalid_argument
{
    public:
        ConversionError(std::string string, std::string type);
};

#endif