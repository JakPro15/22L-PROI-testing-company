#include "simulation/inputfilehandler.h"

int main()
{
    Simulation sim(200, 200, 200);
    OutputHandler out("simulationlog.txt");
    InputFileHandler handler(sim, out, "producers.txt", "games.txt", "testsers.txt", "managers.txt");

    std::vector<std::shared_ptr<Tester>> testers;

    testers.push_back(handler.createTester());
}