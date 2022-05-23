#ifndef _WORKER_H
#define _WORKER_H

#include "abstractworker.h"


class Worker: public AbstractWorker
{
    private:
        // Throws InvalidId if the object's id is invalid for a Worker object.
        void checkId() const;

    protected:
        // Returns the unique name of the worker.
        virtual std::string getUniqueName() const noexcept;
        // Unique id of a worker.
        const int id;
        // Name of the worker.
        std::string name;
        // Surname of the worker.
        std::string surname;
        // Protected constructor that doesn't check ID - used in derived classes with different ID sets.
        // First argument (char) used only to differentiate from other constructors.
        Worker(char, int id, std::string name, std::string surname);
    public:
        // These constants define the ID limits for this class.
        const int minId = 8000001;
        const int maxId = 8999999;

        // Creates an object of class Worker.
        Worker(int id, std::string name, std::string surname);

        // Empty virtual destructor - for inheritance.
        ~Worker() override;

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

        //Returns true xor false if objects are equal or not accordingly comparing only their ids.
        bool operator==(const Worker& worker) const noexcept;
        bool operator!=(const Worker& worker) const noexcept;

        // Puts the unique name of the worker obtained from getUniqueName into the stream.
        friend std::ostream& operator<<(std::ostream& os, const Worker& worker) noexcept;
};

#endif