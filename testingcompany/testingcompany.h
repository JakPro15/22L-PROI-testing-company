#ifndef TESTINGCOMPANY_H
#define TESTINGCOMPANY_H

#include "testingdatabase.h"


class AbstractGame;


class TestingCompany
{
private:
    // Current amount of effort the company can use.
    unsigned int effort;
public:
    TestingCompany(...) {}
    ~TestingCompany() {}
    int getRequestId() { return 11000001; }

    // Adds increases effort held by the company by specified amount.
    void addEffort(unsigned int effort) {this->effort += effort;}

    void testingFinished(const AbstractGame &game) {}
    void paymentDone(const AbstractGame &game) {}
    void sendTestingRequest(const AbstractGame &game) {}

    bool operator==(const TestingCompany &company) const noexcept { return this == &company; }
    bool operator!=(const TestingCompany &company) const noexcept { return not (*this == company); };
};


#endif
