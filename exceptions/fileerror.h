#ifndef _FILEERROR_H
#define _FILEERROR_H
#include <stdexcept>

/*
Thrown when a file can not be opened.
*/
class FileError: public std::invalid_argument
{
    public:
        FileError(std::string fileName);
        FileError(char c, std::string msg);
};


#endif