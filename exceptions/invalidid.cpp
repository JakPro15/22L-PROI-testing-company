#include "invalidid.h"


InvalidId::InvalidId(std::string typeName, int id):
    std::invalid_argument("Invalid id given to " + typeName + ": " + std::to_string(id))
{}
