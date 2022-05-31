#ifndef _OUTPUTHANDLER_H
#define _OUTPUTHANDLER_H

#include <iostream>
#include <fstream>

#define debug true

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
            if (debug)
            {
            file << object;
            outputStream << object;
            }
            return *this;
        }

        OutputHandler& operator<<(OutputHandler& (*func)(OutputHandler&));

        // Inserts a new line into the stream and waits 3 seconds.
        static OutputHandler& endlWait(OutputHandler& out);
};

#endif