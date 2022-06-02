#include "simulation/simulation.h"
#include <exception>


int main(int argc, char *argv[])
{
    if(argc != 9)
    {
        std::cerr << "The program takes exactly 8 command line arguments." << std::endl;
        return 1;
    }

    int testersAmount, managersAmount, hours;  // not unsigned int in order to throw error when user inputs a negative number
    try
    {
        testersAmount = std::stoi(argv[1]);
        managersAmount = std::stoi(argv[2]);
        hours = std::stoi(argv[8]);
        if(testersAmount <= 0)
        {
            throw std::invalid_argument(argv[1]);
        }
        if(managersAmount <= 0)
        {
            throw std::invalid_argument(argv[2]);
        }
        if(hours <= 0)
        {
            throw std::invalid_argument(argv[8]);
        }
    }
    catch(const std::invalid_argument& e)
    {
        std::cerr << "The first two, and the last parameters of the program must be positive integers." << std::endl;
        return 2;
    }
    catch(const std::out_of_range& e)
    {
        std::cerr << "The first two, and the last parameters of the program must be integers in range of the int type.";
        return 3;
    }

    try
    {
        Simulation sim(testersAmount, managersAmount, argv[3], argv[4], argv[5], argv[6], argv[7]);
        sim.simulate(hours);
        return 0;
    }
    catch(const ShutdownException& e)
    {
        std::cerr << e.what() << '\n';
        return 4;
    }
}