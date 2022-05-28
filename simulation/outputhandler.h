#ifndef _OUTPUTHANDLER_H
#define _OUTPUTHANDLER_H

#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>

// This class handles the output of the simulation.

class OutputHandler
{
    private:
        // File to which informations will be saved.
        std::ofstream file;

        // Stream to which the informations will be put (std::cout)
        std::ostream& outputStream;

    public:
        // Constructor allowing for choice of output file. Output stream will always be std::cout.
        // Throws exception when file can't be opened.
        OutputHandler(std::string fileName);

        // File is closed when object is destroyed.
        ~OutputHandler();

        // Operator which allows to put any object into both the output file and the output stream.
        template<typename T>
        OutputHandler& operator<<(const T& object)
        {
            file << object << std::endl;
            outputStream << object << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(3000));
            return *this;
        }
};

#endif