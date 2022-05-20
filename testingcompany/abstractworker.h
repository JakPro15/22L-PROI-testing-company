#ifndef _ABSTRACTWORKER_H
#define _ABSTRACTWORKER_H

#include <string>


class AbstractWorker
{
    public:

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
};

#endif