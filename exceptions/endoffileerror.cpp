#include "endoffileerror.h"

EndOfFileError::EndOfFileError():
    std::logic_error("End of file has been reached while trying to read data from file"){}