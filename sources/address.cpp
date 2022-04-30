#include <stdexcept>
#include <algorithm>
#include "../address.h"
#include "../exceptions/emptynameexception.h"
#include "../exceptions/zeroexception.h"
#include "../exceptions/incorrectaddressexception.h"


Address::Address(std::string cstreetName, unsigned int chouseNumber,
            unsigned int capartmentNumber, std::string ccityName,
            std::string cpostCode) {
    std::string nameCopy = cstreetName;
    nameCopy.erase(std::remove_if(nameCopy.begin(), nameCopy.end(), ::isspace), nameCopy.end());
    if(!nameCopy.empty())
    {
        streetName = cstreetName;
    }
    else
    {
        throw EmptyNameException("Street name can't be empty");
    }
    if (chouseNumber != 0)
    {
    houseNumber = chouseNumber;
    }
    else
    {
        throw ZeroException("House number");
    }
    apartmentNumber = capartmentNumber;
    std::string snameCopy = ccityName;
    snameCopy.erase(std::remove_if(snameCopy.begin(), snameCopy.end(), ::isspace), snameCopy.end());
    if(!snameCopy.empty())
    {
        cityName = ccityName;
    }
    else
    {
        throw EmptyNameException("City name can't be empty");
    }
    if (cpostCode.length() != 6)
    {
        throw IncorrectAddressException("Incorrect post code length");
    }
    bool onlyNumbers = true;
    for (int i = 0; i < 2; i++)
    {
        if ((int(cpostCode[i]) < int('0')) || (int(cpostCode[i]) > int('9')))
        {
            onlyNumbers = false;
        }
    }
    if (cpostCode[2] != '-')
    {
        onlyNumbers = false;
    }
    for (int i = 3; i < 6; i++)
    {
        if ((int(cpostCode[i]) < int('0')) || (int(cpostCode[i]) > int('9')))
        {
            onlyNumbers = false;
        }
    }
    if (onlyNumbers)
    {
        postCode = std::string(cpostCode);
    }
    else
    {
        throw IncorrectAddressException(
            "Post code must consist of a set of two numbers and a set of three numbers separated by a comma"
            );
    }
}

Address::Address() {
    streetName = "Default";
    houseNumber = 1;
    apartmentNumber = 1;
    cityName = "Defaultsville";
    postCode = "00-000";
}

std::string Address::getStreetName() const {
    return streetName;
}

unsigned int Address::getHouseNumber() const {
    return houseNumber;
}

unsigned int Address::getApartmentNumber() const {
    return apartmentNumber;
}

std::string Address::getCityName() const {
    return cityName;
}

std::string Address::getPostCode() const {
    return postCode;
}

void Address::setStreetName(std::string newName) {
    std::string nameCopy = newName;
    nameCopy.erase(std::remove_if(nameCopy.begin(), nameCopy.end(), ::isspace), nameCopy.end());
    if(!nameCopy.empty())
    {
        streetName = newName;
    }
    else
    {
        throw EmptyNameException("Street name can't be empty");
    }
}

void Address::setHouseNumber(unsigned int newHnumber) {
    if (newHnumber != 0)
    {
    houseNumber = newHnumber;
    }
    else
    {
        throw ZeroException("House number");
    }
}

void Address::setApartmentNumber(unsigned int newAnumber) {
    apartmentNumber = newAnumber;
}

void Address::setCityName(std::string newCname) {
    std::string nameCopy = newCname;
    nameCopy.erase(std::remove_if(nameCopy.begin(), nameCopy.end(), ::isspace), nameCopy.end());
    if(!nameCopy.empty())
    {
        cityName = newCname;
    }
    else
    {
        throw EmptyNameException("City name can't be empty");
    }
}

void Address::setPostCode(std::string new_postCode) {
    if (new_postCode.length() != 6)
    {
        throw IncorrectAddressException("Incorrect post code length");
    }
    bool onlyNumbers = true;
    for (int i = 0; i < 2; i++)
    {
        if ((int(new_postCode[i]) < int('0')) || (int(new_postCode[i]) > int('9')))
        {
            onlyNumbers = false;
        }
    }
    if (new_postCode[2] != '-')
    {
        onlyNumbers = false;
    }
    for (int i = 3; i < 6; i++)
    {
        if ((int(new_postCode[i]) < int('0')) || (int(new_postCode[i]) > int('9')))
        {
            onlyNumbers = false;
        }
    }
    if (onlyNumbers)
    {
        postCode = std::string(new_postCode);
    }
    else
    {
        throw IncorrectAddressException("Post code must contain only numbers");
    }
}

bool Address::operator==(const Address& secondAddress) const {
    return (
        (streetName == secondAddress.streetName) &&
        (houseNumber == secondAddress.houseNumber) &&
        (apartmentNumber == secondAddress.apartmentNumber) &&
        (cityName == secondAddress.cityName) &&
        (postCode == secondAddress.postCode)
    );
}

bool Address::operator!=(const Address& secondAddress) const {
    return !(*this == secondAddress);
}

std::ostream& operator<<(std::ostream& os, const Address& address) {
    os << "ul." << address.streetName << " " << address.houseNumber;
    if (address.apartmentNumber != 0)
    {
        os << "/" << address.apartmentNumber;
    }
    os << " " << address.postCode << " " << address.cityName;
    return os;
}