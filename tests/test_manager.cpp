#include "catch.hpp"
#include "../testingcompany/manager.h"
#include "../games/game.h"
#include "../exceptions.h"
#include "../testingcompany/testingcompany.h"
#include "../testingcompany/testingrecord.h"
#include "../simulation/outputhandler.h"
#include "../simulation/simulation.h"
#include <sstream>

TEST_CASE("Manager methods", "[Manager]")
{
    OutputHandler out(18000001, "../simulationlog.txt");
    TestingCompany company(15000001, out);
    Manager piekarz(9000001, "Paweł", "Piekarski", company, out);

    SECTION("Constructor and getters")
    {
        Manager butcher(9000002, "Jan", "Rzeźnicki", company, out);

        CHECK(butcher.id == 9000002);
        CHECK(butcher.getName() == "Jan");
        CHECK(butcher.getSurname() == "Rzeźnicki");

    }

    SECTION("Constructor-exceptions")
    {
        CHECK_THROWS_AS(Manager(1, "Jan", "Kowalski", company, out), InvalidId);
        CHECK_THROWS_AS(Manager(9000002, "\n", "Kowalski", company, out), EmptyNameException);
        CHECK_THROWS_AS(Manager(9000002, "Jan", "   ", company, out), EmptyNameException);
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

    SECTION("Do work")
    {
        Simulation sim(3, 0, "../producers.txt", "../games.txt", "../testers.txt", "../managers.txt", "../simulationlog.txt");
        Producer pr(out, 14000001, "Pr", Address("SN", 2, 5, "SNville", "12-345"), sim, company);
        Game game(1000001, "Bruh", pr, 1000, AbstractGame::Simple, 5);
        company.obtainTestingRequest(game);
        unsigned int effort = company.getEffort();
        piekarz.doWork();
        assert(company.getEffort() == effort + piekarz.getProductivity());
    }

    SECTION("Comparison operators")
    {
        Manager evil_clone(9000001, "Graweł", "Piekarski", company, out);
        Manager random(9000002, "Losowy", "Typ", company, out);

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

        Manager random(9000002, "Losowy", "Typ", company, out);

        stream1 << random;
        stream2 << "Manager 2";

        CHECK(stream1.str() == stream2.str());
    }
}