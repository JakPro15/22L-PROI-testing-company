#ifndef _ABSTRACTWORKER_H
#define _ABSTRACTWORKER_H

#include <string>


class AbstractWorker
{
    public:

        // Empty virtual destructor - for inheritance.
        virtual ~AbstractWorker()=0;

        // Returns the identifier of the worker.
        virtual int getId() const noexcept=0;

        // Sets the name of the worker. Empty (all whitespace) names are not allowed.
        virtual void setName(std::string title)=0;
        // Returns the name of the worker.
        virtual std::string getName() const noexcept=0;

        // Sets the surname of the worker. Empty (all whitespace) surnames are not allowed.
        virtual void setSurname(std::string title)=0;
        // Returns the surname of the worker.
        virtual std::string getSurname() const noexcept=0;

        //Returns true xor false if objects are equal or not accordingly.
        virtual bool operator==(const AbstractWorker& worker)=0;
        virtual bool operator!=(const AbstractWorker& worker)=0;
};

#endif