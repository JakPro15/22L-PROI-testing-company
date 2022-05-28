#include "shutdownexception.h"

ShutdownException::ShutdownException():
    std::logic_error("An exception has occured, simulation is shut down."){}