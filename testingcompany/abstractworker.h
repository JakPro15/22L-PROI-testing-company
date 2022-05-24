#ifndef _ABSTRACTWORKER_H
#define _ABSTRACTWORKER_H

#include "checkallwhitespace.h"
#include <string>


class AbstractWorker
{
    protected:
        // Returns the unique name of the worker.
        virtual std::string getUniqueName() const noexcept=0;
        // Protected constructor to initialize ID and producer properly
        AbstractWorker(int id, std::string name, std::string surname):
        id(id), name(name), surname(surname)
        {
            if (checkAllWhitespace(name))
            {
                throw EmptyNameException();
            }
            if (checkAllWhitespace(surname))
            {
                throw EmptyNameException("Surname");
            }
        }
    public:
        // Unique ID of the game assigned at creation.
        const int id;

        // Name of the worker.
        std::string name;

        // Surname of the worker.
        std::string surname;

        // Productivity of the worker.
        //(determines how much can he test in an hour if he's a tester or how much effort he puts in per hour if he's manager).
        unsigned int productivity;

        // Copying of AbstractWorker is forbidden (IDs wouldn't be unique).
        AbstractWorker(const AbstractWorker&)=delete;
        AbstractWorker& operator=(const AbstractWorker&)=delete;

        // Empty virtual destructor - for inheritance.
        virtual ~AbstractWorker() {};

        // Returns the identifier of the worker.
        virtual int getId() const noexcept=0;

        // Sets the name of the worker. Empty (all whitespace) names are not allowed.
        virtual void setName(std::string name)=0;
        // Returns the name of the worker.
        virtual std::string getName() const noexcept=0;

        // Sets the surname of the worker. Empty (all whitespace) surnames are not allowed.
        virtual void setSurname(std::string surname)=0;
        // Returns the surname of the worker.
        virtual std::string getSurname() const noexcept=0;

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