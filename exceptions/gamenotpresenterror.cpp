#include "gamenotpresenterror.h"


GameNotPresentError::GameNotPresentError():
    std::logic_error("Attempted to change a game in ProducerDatabase when it is not there.")
{}
