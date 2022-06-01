#include "catch.hpp"
#include "../testingcompany/testingcompany.h"
#include "../simulation/outputhandler.h"
#include "../simulation/simulation.h"
#include "../games/game.h"
#include <sstream>

TEST_CASE("Testing company methods", "[TestingCompany]")
{
    OutputHandler out(18000001, "../simulationlog.txt");
    TestingCompany testingCompany(15000001, out);

    SECTION("Constructor and getters")
    {
        TestingCompany company(15000001, out);
        CHECK(company.id == 15000001);
        CHECK(company.getEffort() == 0);
        CHECK(company.getRequestId() == 11000001);
        CHECK(company.getRequestId() == 11000002);
        CHECK(company.getRecords() == 0);
        CHECK(company.getWorkers() == 0);
        CHECK(company.getTesters() == 0);
    }

    SECTION("Wrong constructor")
    {
        CHECK_THROWS_AS(TestingCompany(7, out), InvalidId);
    }

    SECTION("Add effort")
    {
        testingCompany.addEffort(20);
        CHECK(testingCompany.getEffort() == 20);
    }

    SECTION("Add tester")
    {
        std::shared_ptr<Tester> tester = std::make_shared<Tester>(10000001, "Paweł", "Piekarski", testingCompany, out);
        testingCompany.addTester(tester);
        CHECK(testingCompany.getWorkers() == 1);
        CHECK(testingCompany.getTesters() == 1);
    }

    SECTION("Add manager")
    {
        std::shared_ptr<Manager> manager = std::make_shared<Manager>(9000001, "Paweł", "Piekarski", testingCompany, out);
        testingCompany.addManager(manager);
        CHECK(testingCompany.getWorkers() == 1);
        CHECK(testingCompany.getTesters() == 0);
    }

    SECTION("Is there work")
    {
        Simulation sim(3, 0, "../producers.txt", "../games.txt", "../testers.txt", "../managers.txt", "../simulationlog.txt");
        Producer pr(out, 14000001, "Pr", Address("SN", 2, 5, "SNville", "12-345"), sim, testingCompany);
        Game game(1000001, "Bruh", pr, 1000, AbstractGame::Simple, 5);
        CHECK(testingCompany.isThereWork() == false);
        testingCompany.obtainTestingRequest(game);
        CHECK(testingCompany.isThereWork() == true);
    }

    SECTION("Comparison operators")
    {
        TestingCompany testingCompany2(15000001, out);
        CHECK(testingCompany == testingCompany);
        CHECK_FALSE(testingCompany != testingCompany);
        CHECK(testingCompany != testingCompany2);
        CHECK_FALSE(testingCompany == testingCompany2);
    }

    SECTION("Stream operator")
    {
        std::stringstream stream1, stream2;
        stream1 << testingCompany;
        stream2 << "TestingCompany 1";

        CHECK(stream1.str() == stream2.str());

        TestingCompany testingCompany2(15009000, out);

        stream1.str("");
        stream1.clear();
        stream2.str("");
        stream2.clear();

        stream1 << testingCompany2;
        stream2 << "TestingCompany 9000";

        CHECK(stream1.str() == stream2.str());
    }
}