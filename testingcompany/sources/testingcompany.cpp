#include "../testingcompany.h"
#include "../../exceptions.h"

TestingCompany::TestingCompany(...)
{

}

int TestingCompany::getRequestId()
{
    int returnId  = currentRequestId++;
    if (returnId > 11999999)
    {
        return returnId;
    }
    else
    {
        throw InvalidId("request", returnId);
    }
}