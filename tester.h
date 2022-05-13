#ifndef TESTER_H
#define TESTER_H
#include "testingrecord.h"
#include <memory>


class TestingRecord;


// WERSJA TYMCZASOWA DO TESTÓW
class Tester
{
    int prod;
    bool busyness;
    TestingRecord *gameRecord;
public:
    Tester(int prod): prod(prod), busyness(false), gameRecord(nullptr) {}

    // NIE ZMIENIAJ ARGUMENTÓW ANI NAZW ANI TYPÓW WARTOŚCI ZWRACANYCH Z PONIŻSZYCH FUNKCJI
    // TO ROZWALI TestingRecord
    // TYLKO SAMA IMPLEMENTACJA MA SIĘ ZMIENIAĆ
    int getProductivity()
    { return prod; }  // average should be 5
    void setBusy(bool bus)
    { busyness = bus; }
    bool getBusy()
    { return busyness; }
    void setTestedGameRecord(TestingRecord *record)
    { gameRecord = record; }
    TestingRecord* getTestedGameRecord()
    { return gameRecord; }
};


#endif
