#include "../simulation.h"
#include "../../exceptions.h"

Simulation::Simulation(unsigned int iterations, unsigned int testersAmount, unsigned int managersAmount):
    iterations(iterations), testersAmount(testersAmount), managersAmount(managersAmount), currentProducerRecordId(13000001)
{}

TestingCompany& Simulation::getTestingCompany() noexcept
{
    return testingCompany;
}

int Simulation::getProducerRecordId()
{
    int return_id  = currentProducerRecordId++;
    if (return_id > 13999999)
    {
        throw InvalidId("producer record", return_id);
    }
    return return_id;
}

bool Simulation::operator==(const Simulation &simulation) const noexcept
{
    return this == &simulation;
}

bool Simulation::operator!=(const Simulation &simulation) const noexcept
{
    return not (*this == simulation);
}

std::ostream& operator<<(std::ostream& os, const Simulation& simulation) noexcept
{
    os << "simulation";
}