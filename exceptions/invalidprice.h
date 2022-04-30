#ifndef INVALIDPRICE_H
#define INVALIDPRICE_H
#include <stdexcept>


/*
Thrown when attempting to set a price to an invalid value
(negative, negative amount of gr, over 100 gr via a setter)
*/
class InvalidPrice: public std::invalid_argument
{
public:
    InvalidPrice(int zl, int gr);
    InvalidPrice(int priceInGr);
};


#endif
