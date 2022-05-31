#include "simulation/simulation.h"

int main()
{
    try
    {
        Simulation sim(4, 2, "producers.txt", "games.txt", "testers.txt", "managers.txt", "simulationlog.txt");
        sim.simulate(50);
        return 0;
    }
    catch(const ShutdownException& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
}