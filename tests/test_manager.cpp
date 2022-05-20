#include "catch.hpp"
#include "../testingcompany/manager.h"
#include "../games/game.h"
#include "../exceptions.h"
#include <sstream>

TEST_CASE("Manager methods", "[Manager]")
{
    TestingCompany company;
    Manager piekarz(9000001, "Paweł", "Piekarski", 4, company);

    SECTION("Constructor and getters")
    {
        Manager butcher(9000002, "Jan", "Rzeźnicki", 4, company);

        CHECK(butcher.getId() == 9000002);
        CHECK(butcher.getName() == "Jan");
        CHECK(butcher.getSurname() == "Rzeźnicki");
        CHECK(butcher.getProductivity() == 4);

    }

    SECTION("Constructor-exceptions")
    {
        CHECK_THROWS_AS(Manager(1, "Jan", "Kowalski", 5, company), InvalidId);
        CHECK_THROWS_AS(Manager(9000002, "\n", "Kowalski", 7, company), EmptyNameException);
        CHECK_THROWS_AS(Manager(9000002, "Jan", "   ", 1, company), EmptyNameException);
        CHECK_THROWS_AS(Manager(9000003, "Jan", "Kowalski", 0, company), ProductivityOutOfRangeException);
        CHECK_THROWS_AS(Manager(9000003, "Jan", "Kowalski", 90, company), ProductivityOutOfRangeException);
    }

    SECTION("Setters")
    {
        piekarz.setName("Graweł");
        CHECK(piekarz.getName() == "Graweł");

        piekarz.setSurname("Rzeźnicki");
        CHECK(piekarz.getSurname() == "Rzeźnicki");
    }

    SECTION("Setters-exceptions")
    {
        CHECK_THROWS_AS(piekarz.setName("\t\t"), EmptyNameException);
        CHECK_THROWS_AS(piekarz.setSurname("   \n\t"), EmptyNameException);
    }

    SECTION("Comparison operators")
    {
        Manager evil_clone(9000001, "Graweł", "Piekarski", 9, company);
        Manager random(9000002, "Losowy", "Typ", 5, company);

        CHECK((piekarz == evil_clone) == true);
        CHECK((piekarz != evil_clone) == false);

        CHECK((piekarz == random) == false);
        CHECK((piekarz != random) == true);
    }

    SECTION("Stream operator")
    {
        std::stringstream stream1, stream2;

        stream1 << piekarz;
        stream2 << "Manager 1";

        CHECK(stream1.str() == stream2.str());

        stream1.str("");
        stream1.clear();
        stream2.str("");
        stream2.clear();

        Manager random(9000002, "Losowy", "Typ", 7, company);

        stream1 << random;
        stream2 << "Manager 2";

        CHECK(stream1.str() == stream2.str());
    }
}