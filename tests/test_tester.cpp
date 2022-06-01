#include "catch.hpp"
#include "../testingcompany/tester.h"
#include "../games/game.h"
#include "../producer/producer.h"
#include "../testingcompany/testingcompany.h"
#include "../testingcompany/testingrecord.h"
#include "../simulation/simulation.h"
#include "../exceptions.h"
#include <sstream>

TEST_CASE("Tester methods", "[Tester]")
{
    OutputHandler out("../simulationlog.txt");
    TestingCompany company(out);
    Tester piekarz(10000001, "Paweł", "Piekarski", company, out);

    SECTION("Constructor and getters")
    {
        Tester butcher(10000002, "Jan", "Rzeźnicki", company, out);

        CHECK(butcher.getId() == 10000002);
        CHECK(butcher.getName() == "Jan");
        CHECK(butcher.getSurname() == "Rzeźnicki");
        CHECK(butcher.getBusy() == false);
        CHECK(butcher.getTestedGameRecord() == nullptr);
    }

    SECTION("Constructor-exceptions")
    {
        CHECK_THROWS_AS(Tester(1, "Jan", "Kowalski", company, out), InvalidId);
        CHECK_THROWS_AS(Tester(10000002, "\n", "Kowalski", company, out), EmptyNameException);
        CHECK_THROWS_AS(Tester(10000002, "Jan", "   ", company, out), EmptyNameException);
    }

    SECTION("Setters")
    {
        piekarz.setName("Graweł");
        CHECK(piekarz.getName() == "Graweł");

        piekarz.setSurname("Rzeźnicki");
        CHECK(piekarz.getSurname() == "Rzeźnicki");

        piekarz.setBusy(true);
        CHECK(piekarz.getBusy() == true);

        Simulation sim(3, 0, "../producers.txt", "../games.txt", "../testers.txt", "../managers.txt", "../simulationlog.txt");
        Producer pr(out, 14000001, "Pr", Address("SN", 2, 5, "SNville", "12-345"), sim, company);
        Game game(1000001, "Bruh", pr, 1000, AbstractGame::Simple, 5);
        TestingRecord record(out, 6000003, game, 100);
        piekarz.setTestedGameRecord(&record);
        CHECK(piekarz.getTestedGameRecord() == &record);
    }

    SECTION("Setters-exceptions")
    {
        CHECK_THROWS_AS(piekarz.setName("\t\t"), EmptyNameException);
        CHECK_THROWS_AS(piekarz.setSurname("   \n\t"), EmptyNameException);
    }

    SECTION("Comparison operators")
    {
        Tester evil_clone(10000001, "Graweł", "Piekarski", company, out);
        Tester random(10000002, "Losowy", "Typ", company, out);

        CHECK((piekarz == evil_clone) == true);
        CHECK((piekarz != evil_clone) == false);

        CHECK((piekarz == random) == false);
        CHECK((piekarz != random) == true);
    }

    SECTION("Stream operator")
    {
        std::stringstream stream1, stream2;

        stream1 << piekarz;
        stream2 << "Tester 1";

        CHECK(stream1.str() == stream2.str());

        stream1.str("");
        stream1.clear();
        stream2.str("");
        stream2.clear();

        Tester random(10000002, "Losowy", "Typ", company, out);

        stream1 << random;
        stream2 << "Tester 2";

        CHECK(stream1.str() == stream2.str());
    }
}