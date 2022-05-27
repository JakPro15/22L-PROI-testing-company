#ifndef _CONVERSIONERROR_H
#define _CONVERSIONERROR_H

#include <stdexcept>

class ConversionError: public std::invalid_argument
{
    public:
        ConversionError(std::string string, std::string type);
};

#endif