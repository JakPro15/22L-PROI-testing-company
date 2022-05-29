#include "simulation/simulation.h"

int main()
{
    try
    {
        Simulation sim(200, 3, 0, "producers.txt", "games.txt", "testers.txt", "managers.txt", "simulationlog.txt");
        sim.simulate();
        return 0;
    }
    catch(const ShutdownException& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
}