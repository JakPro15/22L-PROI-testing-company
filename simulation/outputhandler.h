#ifndef _OUTPUTHANDLER_H
#define _OUTPUTHANDLER_H

#define PROI_Projekt_tests

#include <iostream>
#include <fstream>

// This class handles the output of the simulation.

class OutputHandler
{
    public:
        // Unique ID of the output handler assigned at creation.
        const int id;

    private:
        // Throws InvalidId if the object's id is invalid for a OutputHandler object.
        void checkId() const;

        // File to which informations will be saved.
        std::ofstream file;

        // Stream to which the informations will be put (std::cout)
        std::ostream& outputStream;

    public:
        // These constants define the ID limits for this class.
        static const int minId = 18000001;
        static const int maxId = 18999999;

        // Constructor allowing for choice of output file. Output stream will always be std::cout.
        // Throws exception when file can't be opened.
        OutputHandler(int id, std::string fileName);

        // File is closed when object is destroyed.
        ~OutputHandler();

        // Copying of OutputHandler is forbidden (IDs wouldn't be unique).
        OutputHandler(const OutputHandler&)=delete;
        OutputHandler& operator=(const OutputHandler&)=delete;

        // Operator which allows to put any object into both the output file and the output stream.
        template<typename T>
        OutputHandler& operator<<(const T& object)
        {
#ifndef PROI_Projekt_tests  // no printing in tests
            file << object;
            outputStream << object;
#endif
            return *this;
        }

        OutputHandler& operator<<(OutputHandler& (*func)(OutputHandler&));

        // Inserts a new line into the stream and waits 1 second.
        static OutputHandler& endlWait(OutputHandler& out);
};

#endif