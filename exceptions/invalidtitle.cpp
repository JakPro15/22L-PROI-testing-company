#include "invalidtitle.h"


InvalidTitle::InvalidTitle(std::string title):
    std::invalid_argument("Invalid title given to Game or a derived class: " + title)
{}
