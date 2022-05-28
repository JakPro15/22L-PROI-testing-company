#ifndef _SHUTDOWN_EXCEPTION_H
#define _SHUTDOWN_EXCEPTION_H
#include <stdexcept>


/*
Thrown when simulation needs to get shut down due to another exception
*/
class ShutdownException: public std::logic_error
{
    public:
        ShutdownException();
};
#endif