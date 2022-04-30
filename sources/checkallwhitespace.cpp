#include "../checkallwhitespace.h"


bool checkAllWhitespace(std::string string)
{
    // Whitespace characters are: space, HT, LF, VT, FF, CR
    if(string.find_first_not_of(" \t\n\v\f\r") == std::string::npos)
    {
        return true;
    }
    else
    {
        return false;
    }
}
