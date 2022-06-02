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

    Address address2("Bonk", 11, 1, "Bonkstown", "00-001");
    CHECK(address2.getStreetName() == "Bonk");
    CHECK(address2.getHouseNumber() == 11);
    CHECK(address2.getApartmentNumber() == 1);
    CHECK(address2.getCityName() == "Bonkstown");
    CHECK(address2.getPostCode() == "00-001");

    SECTION("empty names")
    {
        CHECK_THROWS_AS(Address("  ", 12, 0, "Lidzbark", "13-230"), EmptyNameException);
        CHECK_THROWS_AS(Address("Słoneczna", 12, 0, "", "13-230"), EmptyNameException);
        CHECK_THROWS_AS(Address("Słoneczna", 12, 0, "Lidzbark", "\n"), IncorrectAddressException);
    }
    SECTION("house number equal to zero")
    {
        CHECK_THROWS_AS(Address("Słoneczna", 0, 0, "Lidzbark", "13-230"), InvalidHouseNumberError);
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
        CHECK_THROWS_AS(address.setHouseNumber(0),  InvalidHouseNumberError);
        CHECK_THROWS_AS(address.setCityName("    \n"), EmptyNameException);
        CHECK_THROWS_AS(address.setPostCode("13 230"), IncorrectAddressException);
        CHECK_THROWS_AS(address.setPostCode("1a-230"), IncorrectAddressException);
        CHECK_THROWS_AS(address.setPostCode("13-2x0"), IncorrectAddressException);
        CHECK_THROWS_AS(address.setPostCode("13-2137"), IncorrectAddressException);
    }

    SECTION("comparison")
    {
        Address address_copy = address;
        CHECK(address == address_copy);
        CHECK(address2 != address_copy);
    }

    SECTION("stream")
    {
        std::stringstream stream1, stream2;
        stream1 << address2;
        stream2 << "ul.Bonk 11/1 00-001 Bonkstown";
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