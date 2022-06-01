#include "simulation/simulation.h"
#include <exception>


int main(int argc, char *argv[])
{
    if(argc != 8)
    {
        std::cerr << "The program takes exactly 7 command line arguments." << std::endl;
        return 1;
    }

    int testersAmount, managersAmount;  // not unsigned int in order to throw error when user inputs a negative number
    try
    {
        testersAmount = std::stoi(argv[1]);
        managersAmount = std::stoi(argv[2]);
        if(testersAmount <= 0)
        {
            throw std::invalid_argument(argv[1]);
        }
        if(managersAmount <= 0)
        {
            throw std::invalid_argument(argv[2]);
        }
    }
    catch(const std::invalid_argument& e)
    {
        std::cerr << "The first two parameters of the program must be positive integers." << std::endl;
        return 2;
    }
    catch(const std::out_of_range& e)
    {
        std::cerr << "The first two parameters of the program must be integers in range of the int type.";
        return 3;
    }

    try
    {
        Simulation sim(testersAmount, managersAmount, argv[3], argv[4], argv[5], argv[6], argv[7]);
        sim.simulate(50);
        return 0;
    }
    catch(const ShutdownException& e)
    {
        std::cerr << e.what() << '\n';
        return 4;
    }
}