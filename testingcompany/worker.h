#ifndef _WORKER_H
#define _WORKER_H

#include "abstractworker.h"

class TestingCompany;
class OutputHandler;


class Worker: public AbstractWorker
{
    private:
        // Throws InvalidId if the object's id is invalid for a Worker object.
        void checkId() const;

    protected:
        // Name of the worker.
        std::string name;

        // Surname of the worker.
        std::string surname;

        // Productivity of the worker.
        //(determines how much can he test in an hour if he's a tester or how much effort he puts in per hour if he's manager).
        unsigned int productivity;

        // Reference to the company in which the worker is employed.
        TestingCompany& company;

        // Reference to the output handler.
        OutputHandler& out;

        // Returns the unique name of the worker.
        virtual std::string getUniqueName() const noexcept;
        // Protected constructor that doesn't check ID - used in derived classes with different ID sets.
        // First argument (char) used only to differentiate from other constructors.
        Worker(char, int id, std::string name, std::string surname, TestingCompany& company, OutputHandler& out);
        
    public:
        // These constants define the ID limits for this class.
        static const int minId = 8000001;
        static const int maxId = 8999999;

        // Creates an object of class Worker.
        Worker(int id, std::string name, std::string surname, TestingCompany& company, OutputHandler& out);

        // Empty virtual destructor - for inheritance.
        ~Worker() override;

        // Copying of Worker is forbidden (IDs wouldn't be unique).
        Worker(const Worker&)=delete;
        Worker& operator=(const Worker&)=delete;


        //Returns the identifier of the worker
        int getId() const noexcept override;

        // Sets the name of the worker. Empty (all whitespace) names are not allowed.
        void setName(std::string name) override;
        // Returns the name of the worker.
        std::string getName() const noexcept override;

        // Sets the surname of the worker. Empty (all whitespace) surnames are not allowed.
        void setSurname(std::string surname) override;
        // Returns the surname of the worker.
        std::string getSurname() const noexcept override;

        // Does nothing, used only in derived classes.
        void doWork() noexcept override {}

        //Returns true xor false if objects are equal or not accordingly comparing only their ids.
        bool operator==(const AbstractWorker& worker) const noexcept override;
        bool operator!=(const AbstractWorker& worker) const noexcept override;

        // Puts the unique name of the worker obtained from getUniqueName into the stream.
        friend std::ostream& operator<<(std::ostream& os, const Worker& worker) noexcept;
};

#endif