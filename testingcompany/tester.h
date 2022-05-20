#ifndef TESTER_H
#define TESTER_H

#include "testingrecord.h"
#include "worker.h"
#include <memory>


class TestingRecord;


class Tester: public Worker
{
    private:
        // Throws InvalidId if the object's id is invalid for a Tester object.
        void checkId() const;

    protected:
        //Returns the unique name of the tester.
        std::string getUniqueName() const noexcept;

        /*
        Productivity of a worker, determines how much progress he makes in testing of a game per hour.
        On average equal to 5.
        */
        unsigned int productivity;

        // Determines if a tester is currently testing a game or not
        bool busyness;

        // Pointer to the game record of the game that is currently being tested by the tester.
        TestingRecord* gameRecord;

    public:
        // These constants define the ID limits for this class.
        const int minId = 10000001;
        const int maxId = 10999999;

        // Creates an object of class Tester with busyness set to false and game record pointer set to nullptr
        Tester(int id, std::string name, std::string surname, unsigned int productivity);

        // Empty virtual destructor - overwritten from Worker.
        ~Tester() override;

        //Returns productivity of the tester.
        unsigned int getProductivity() const noexcept;

        //Sets busyness of tester.
        void setBusy(bool bus);

        //Returns busyness of tester
        bool getBusy() const noexcept;

        //Sets pointer to the game record of the game that is currently being tested by the tester
        void setTestedGameRecord(TestingRecord *record);

        //Returns pointer to the game record of the game that is currently being tested by the tester
        TestingRecord* getTestedGameRecord() const noexcept;

        // Compares only the unique IDs of the testers.
        bool operator==(const Tester& tester) const noexcept;
        bool operator!=(const Tester& tester) const noexcept;

        // Puts the unique name of the tester obtained from getUniqueName into the stream.
        friend std::ostream& operator<<(std::ostream& os, const Tester& tester) noexcept;
};


#endif
