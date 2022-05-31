#ifndef _MANAGER_H
#define _MANAGER_H

#include "worker.h"


class Manager: public Worker
{
    private:
        // Throws InvalidId if the object's id is invalid for a Manager object.
        void checkId() const;

    protected:
        //Returns the unique name of the manager.
        std::string getUniqueName() const noexcept;

    public:
        // These constants define the ID limits for this class.
        static const int minId = 9000001;
        static const int maxId = 9999999;

        // Copying of Manager is forbidden (IDs wouldn't be unique).
        Manager(const Manager&)=delete;
        Manager& operator=(const Manager&)=delete;

        // Creates an object of class Manager.
        Manager(int id, std::string name, std::string surname, TestingCompany& company, OutputHandler& out);

        // Empty virtual destructor - overwritten from Worker.
        ~Manager() override;

        // Returns productivity of the manager.
        unsigned int getProductivity() const noexcept;

        // Adds effort equal to productivity to the company.
        void doWork() noexcept override;

        // Compares only the unique IDs of the managers.
        bool operator==(const Manager& manager) const noexcept;
        bool operator!=(const Manager& manager) const noexcept;

        // Puts the unique name of the manager obtained from getUniqueName into the stream.
        friend std::ostream& operator<<(std::ostream& os, const Manager& manager) noexcept;
};

#endif