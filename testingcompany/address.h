#ifndef _ADDRESS_H
#define _ADDRESS_H

#include <string>
#include <iostream>

/*
Class Address representing address used in the Republic of Poland
*/
class Address
{
    private:
        std::string streetName;
        unsigned int houseNumber;
        unsigned int apartmentNumber;
        std::string cityName;
        std::string postCode;
    public:

        Address(
            std::string streetName, unsigned int houseNumber,
            unsigned int apartmentNumber, std::string cityName,
            std::string postCode
            );
        Address();

        //Returns street name.
        std::string getStreetName() const noexcept;

        //Returns house number.
        unsigned int getHouseNumber() const noexcept;

        //Returns apartment number.
        unsigned int getApartmentNumber() const noexcept;

        //Returns city name.
        std::string getCityName() const noexcept;

        //Returns post code.
        std::string getPostCode() const noexcept;

        //Sets the street name (can't be empty).
        void setStreetName(std::string newName);

        //Sets the house number (can't be == 0).
        void setHouseNumber(unsigned int newHouseNumber);

        /*
        Sets the apartment number (apartment number being equal to 0 means that
        there are no apartments in the building with the chosen house numbee).
        */
        void setApartmentNumber(unsigned int newApartmentNumber);

        //Sets the house number (can't be empty)
        void setCityName(std::string newCityName);

        //Sets the post code (must consist of two digits, a comma and three digits following it)
        void setPostCode(std::string newPostCode);

        //Returns true xor false if objects are equal or not accordingly.
        bool operator==(const Address& secondAddress) const noexcept;
        bool operator!=(const Address& secondAddress) const noexcept;

        //Outputs the object of this class into a stream.
        friend std::ostream& operator<<(std::ostream& os, const Address& address) noexcept;
};

#endif