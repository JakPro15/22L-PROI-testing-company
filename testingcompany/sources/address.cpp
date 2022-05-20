#include "../address.h"
#include "../../exceptions.h"
#include "../checkallwhitespace.h"


Address::Address(std::string cstreetName, unsigned int chouseNumber,
            unsigned int capartmentNumber, std::string ccityName,
            std::string cpostCode) {

    if (checkAllWhitespace(cstreetName))
    {
        throw EmptyNameException("Street name");
    }
    else
    {
        streetName = cstreetName;
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

    if (checkAllWhitespace(ccityName))
    {
        throw EmptyNameException("City name");
    }
    else
    {
        cityName = ccityName;
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

std::string Address::getStreetName() const noexcept {
    return streetName;
}

unsigned int Address::getHouseNumber() const noexcept {
    return houseNumber;
}

unsigned int Address::getApartmentNumber() const noexcept {
    return apartmentNumber;
}

std::string Address::getCityName() const noexcept {
    return cityName;
}

std::string Address::getPostCode() const noexcept {
    return postCode;
}

void Address::setStreetName(std::string newName) {
    if (checkAllWhitespace(newName))
    {
        throw EmptyNameException("Street name");
    }
    else
    {
        streetName = newName;
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
    if (checkAllWhitespace(newCname))
    {
        throw EmptyNameException("City name");
    }
    else
    {
        cityName = newCname;
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

bool Address::operator==(const Address& secondAddress) const noexcept {
    return (
        (streetName == secondAddress.streetName) &&
        (houseNumber == secondAddress.houseNumber) &&
        (apartmentNumber == secondAddress.apartmentNumber) &&
        (cityName == secondAddress.cityName) &&
        (postCode == secondAddress.postCode)
    );
}

bool Address::operator!=(const Address& secondAddress) const noexcept {
    return !(*this == secondAddress);
}

std::ostream& operator<<(std::ostream& os, const Address& address) noexcept {
    os << "ul." << address.streetName << " " << address.houseNumber;
    if (address.apartmentNumber != 0)
    {
        os << "/" << address.apartmentNumber;
    }
    os << " " << address.postCode << " " << address.cityName;
    return os;
}