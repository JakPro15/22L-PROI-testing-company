#include <iostream>
#include <fstream>

class OutputHandler
{
    private:
        // File to which informations will be saved.
        std::ofstream file;

        // Stream to which the informations will be put (std::cout)
        std::ostream& outputStream;

    public:
        OutputHandler(std::string fileName);
        ~OutputHandler();
        template<typename T>
        OutputHandler& operator<<(const T& object);
};
