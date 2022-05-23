#ifndef _MANAGER_H
#define _MANAGER_H

#include "worker.h"


class TestingCompany;


class Manager: public Worker
{
    private:
        // Throws InvalidId if the object's id is invalid for a Manager object.
        void checkId() const;

    protected:

        /*
        Productivity of a worker, determines how much effort he puts in per hour.
        On average equal to 5.
        */
        unsigned int productivity;

        //Returns the unique name of the manager.
        std::string getUniqueName() const noexcept;

    public:
        // These constants define the ID limits for this class.
        const int minId = 9000001;
        const int maxId = 9999999;

        // Pointer to the database of the company in which a manager is employed
        TestingCompany& company;

        // Creates an object of class Manager.
        Manager(int id, std::string name, std::string surname,  unsigned int productivity, TestingCompany& company);

        // Empty virtual destructor - overwritten from Worker.
        ~Manager() override;

        // Returns productivity of the manager.
        unsigned int getProductivity() const noexcept;

        // Adds effort equal to productivity to the company.
        void produceEffort();

        // Compares only the unique IDs of the managers.
        bool operator==(const Manager& manager) const noexcept;
        bool operator!=(const Manager& manager) const noexcept;

        // Puts the unique name of the manager obtained from getUniqueName into the stream.
        friend std::ostream& operator<<(std::ostream& os, const Manager& manager) noexcept;
};

#endif