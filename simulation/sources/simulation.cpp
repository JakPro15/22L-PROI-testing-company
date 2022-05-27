#include "../simulation.h"
#include "../../exceptions.h"

Simulation::Simulation()
{
    current_producer_record_id = 13000001;
}

int Simulation::getProducerRecordId()
{
    int return_id  = current_producer_record_id++;
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