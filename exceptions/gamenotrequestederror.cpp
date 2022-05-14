#include "gamenotrequestederror.h"


GameNotRequestedError::GameNotRequestedError():
    std::logic_error("Attempted to change set a game as tested when its testing hadn't been requested.")
{}
