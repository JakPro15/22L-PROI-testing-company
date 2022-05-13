#ifndef TESTINGCOMPANY_H
#define TESTINGCOMPANY_H

#include "testingdatabase.h"


class TestingCompany
{
private:
    /* data */
public:
    TestingCompany(...) {}
    ~TestingCompany() {}
    int getRequestId() { return 11000001; }
    void testingFinished(const Game &game) {}
};


#endif
