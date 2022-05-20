#include <sstream>
#include "catch.hpp"
#include "../exceptions.h"
#include "../testingcompany/address.h"

TEST_CASE("Address tests")
{
    Address address("Słoneczna", 12, 0, "Lidzbark", "13-230");
    CHECK(address.getStreetName() == "Słoneczna");
    CHECK(address.getHouseNumber() == 12);
    CHECK(address.getApartmentNumber() == 0);
    CHECK(address.getCityName() == "Lidzbark");
    CHECK(address.getPostCode() == "13-230");

    Address default_address = Address();
    CHECK(default_address.getStreetName() == "Default");
    CHECK(default_address.getHouseNumber() == 1);
    CHECK(default_address.getApartmentNumber() == 1);
    CHECK(default_address.getCityName() == "Defaultsville");
    CHECK(default_address.getPostCode() == "00-000");

    SECTION("empty names")
    {
        CHECK_THROWS_AS(Address("  ", 12, 0, "Lidzbark", "13-230"), EmptyNameException);
        CHECK_THROWS_AS(Address("Słoneczna", 12, 0, "", "13-230"), EmptyNameException);
        CHECK_THROWS_AS(Address("Słoneczna", 12, 0, "Lidzbark", "\n"), IncorrectAddressException);
    }
    SECTION("house number equal to zero")
    {
        CHECK_THROWS_AS(Address("Słoneczna", 0, 0, "Lidzbark", "13-230"), ZeroException);
    }
    SECTION("improper post code")
    {
        CHECK_THROWS_AS(Address("Słoneczna", 12, 0, "Lidzbark", "a3-230"), IncorrectAddressException);
        CHECK_THROWS_AS(Address("Słoneczna", 12, 0, "Lidzbark", "13 230"), IncorrectAddressException);
        CHECK_THROWS_AS(Address("Słoneczna", 12, 0, "Lidzbark", "13-b30"), IncorrectAddressException);
        CHECK_THROWS_AS(Address("Słoneczna", 12, 0, "Lidzbark", "13-2301"), IncorrectAddressException);
    }

    SECTION("setters")
    {
        address.setStreetName("A");
        CHECK(address.getStreetName() == "A");
        address.setHouseNumber(1);
        CHECK(address.getHouseNumber() == 1);
        address.setApartmentNumber(5);
        CHECK(address.getApartmentNumber() == 5);
        address.setCityName("A");
        CHECK(address.getCityName() == "A");
        address.setPostCode("11-111");
        CHECK(address.getPostCode() == "11-111");
    }

    SECTION("setters wrong")
    {
        CHECK_THROWS_AS(address.setStreetName("    "), EmptyNameException);
        CHECK_THROWS_AS(address.setHouseNumber(0),  ZeroException);
        CHECK_THROWS_AS(address.setCityName("    \n"), EmptyNameException);
        CHECK_THROWS_AS(address.setPostCode("13 230"), IncorrectAddressException);
        CHECK_THROWS_AS(address.setPostCode("1a-230"), IncorrectAddressException);
        CHECK_THROWS_AS(address.setPostCode("13-2x0"), IncorrectAddressException);
        CHECK_THROWS_AS(address.setPostCode("13-2137"), IncorrectAddressException);
    }

    SECTION("comparison")
    {
        Address address_copy = Address();
        bool a = default_address == address_copy;
        bool b = default_address != address_copy;
        CHECK(a == true);
        CHECK(b == false);
    }

    SECTION("stream")
    {
        std::stringstream stream1, stream2;
        stream1 << default_address;
        stream2 << "ul.Default 1/1 00-000 Defaultsville";
        CHECK(stream1.str() == stream2.str());
        stream1.str("");
        stream1.clear();
        stream2.str("");
        stream2.clear();
        stream1 << address;
        stream2 << "ul.Słoneczna 12 13-230 Lidzbark";
        CHECK(stream1.str() == stream2.str());
    }
}