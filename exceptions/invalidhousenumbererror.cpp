#include "invalidhousenumbererror.h"

InvalidHouseNumberError::InvalidHouseNumberError():
    std::invalid_argument("House number cannot be equal to zero")
{}
