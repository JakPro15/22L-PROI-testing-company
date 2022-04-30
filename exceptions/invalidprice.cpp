#include "invalidprice.h"


InvalidPrice::InvalidPrice(int zl, int gr):
    std::invalid_argument("Negative value given to Price: " + std::to_string(zl) + " zl " + std::to_string(gr) + " gr")
{}


InvalidPrice::InvalidPrice(int priceInGr):
    std::invalid_argument("Negative value given to Price: " + std::to_string(priceInGr) + " gr")
{}
