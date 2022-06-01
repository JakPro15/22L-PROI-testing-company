#ifndef _ABSTRACTWORKER_H
#define _ABSTRACTWORKER_H

#include "../exceptions.h"
#include "checkallwhitespace.h"
#include <string>


class AbstractWorker
{
    protected:
        // Returns the unique name of the worker.
        virtual std::string getUniqueName() const noexcept=0;
        // Protected constructor to initialize ID and producer properly
        AbstractWorker(int id): id(id) {}
    public:
        // Unique ID of the game assigned at creation.
        const int id;

        // Copying of AbstractWorker is forbidden (IDs wouldn't be unique).
        AbstractWorker(const AbstractWorker&)=delete;
        AbstractWorker& operator=(const AbstractWorker&)=delete;

        // Empty virtual destructor - for inheritance.
        virtual ~AbstractWorker()=0;

        // Sets the name of the worker. Empty (all whitespace) names are not allowed.
        virtual void setName(std::string name)=0;
        // Returns the name of the worker.
        virtual std::string getName() const noexcept=0;

        // Sets the surname of the worker. Empty (all whitespace) surnames are not allowed.
        virtual void setSurname(std::string surname)=0;
        // Returns the surname of the worker.
        virtual std::string getSurname() const noexcept=0;

        // Does work according to worker type.
        virtual void doWork() noexcept=0;

        // Compares the given workers.
        virtual bool operator==(const AbstractWorker &worker) const noexcept=0;
        virtual bool operator!=(const AbstractWorker &worker) const noexcept=0;

        // Puts the unique name of the worker obtained from getUniqueName into the stream.
        friend std::ostream& operator<<(std::ostream& os, const AbstractWorker& worker) noexcept
        {
            os << worker.getUniqueName();
            return os;
        }
};

#endif