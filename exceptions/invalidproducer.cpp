#include "invalidproducer.h"


InvalidProducer::InvalidProducer():
    std::invalid_argument("Attempted to add a game that was produced by a different company to a ProducerDatabase.")
{}
