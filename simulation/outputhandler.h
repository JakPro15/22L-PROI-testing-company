#include <iostream>


class OutputHandler
{
public:
    // w tej funkcji ma być jakiś czas spania, żeby użytkownik mógł przeczytać to co zostało wypisane
    // tak jak w wytycznych napisane
    // ma być też std::endl na końcu
    OutputHandler& operator<<(const std::string &string) { return *this; }
};
