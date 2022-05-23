#include <iostream>


class OutputHandler
{
    OutputHandler& operator<<(const std::string &string);
};
