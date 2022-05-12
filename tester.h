#ifndef TESTER_H
#define TESTER_H
#include "testingrecord.h"


class Tester
{
public:
    int getProductivity();  // average should be 5
    void setBusy(bool);
    void setTestedGame(TestingRecord);
};


#endif
