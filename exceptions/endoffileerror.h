#ifndef _ENDOFFILEERROR_H
#define _ENDOFFILERRROR_H
#include <stdexcept>

/*
Thrown when end of file has been reached while trying to read data.
*/
class EndOfFileError: public std::logic_error
{
    public:
        EndOfFileError();
};


#endif