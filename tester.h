#ifndef TESTER_H
#define TESTER_H
#include "testingrecord.h"
#include <memory>


class TestingRecord;


// WERSJA TYMCZASOWA DO TESTÓW
class Tester
{
    int prod;
    bool busy;
    TestingRecord *gameRecord;
public:
    Tester(int prod): prod(prod), busy(false), gameRecord(nullptr) {}

    // NIE ZMIENIAJ ARGUMENTÓW ANI NAZW ANI TYPÓW WARTOŚCI ZWRACANYCH Z PONIŻSZYCH FUNKCJI
    // TO ROZWALI TestingRecord
    // TYLKO SAMA IMPLEMENTACJA MA SIĘ ZMIENIAĆ
    int getProductivity()
    { return prod; }  // average should be 5
    void setBusy(bool bus)
    { busy = bus; }
    bool getBusy()
    { return busy; }
    void setTestedGameRecord(TestingRecord *record)
    { gameRecord = record; }
    TestingRecord* getTestedGameRecord()
    { return gameRecord; }
};


#endif
