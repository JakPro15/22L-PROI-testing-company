#include "../testingcompany/testingdatabase.h"
#include "../testingcompany/testingrecord.h"
#include "../testingcompany/tester.h"
#include "../games/roleplayinggame.h"
#include "../producer/producer.h"
#include "../testingcompany/testingcompany.h"
#include "../simulation/simulation.h"
#include "../exceptions.h"
#include "catch.hpp"
#include <sstream>


TEST_CASE("TestingDatabase constructor and request processing", "[TestingDatabase]")
{
    TestingCompany company;
    OutputHandler out;
    TestingDatabase database(out, 7000001, company);
    Simulation sim;
    TestingCompany tcom;
    Producer pr(out, 14000001, "Pr", Address("SN", 2, 5, "SNville", "12-345"), sim, tcom);
    Game game1(1000001, "G", pr, 100, AbstractGame::Average, 3, true, Price(500));
    RolePlayingGame game2(3000001, "G2", pr, 100, AbstractGame::Complex, 5, 120, 240, true, Price(4000));
    SECTION("Constructor (typical) and getters")
    {
        CHECK(database.id == 7000001);
        CHECK(database.company == company);
        CHECK(database.getGamesBeingTestedAmount() == 0);
        CHECK(database.getGamesWaitingForTestersAmount() == 0);
        CHECK(database.getTestRequestsAmount() == 0);

        TestingCompany company2;
        TestingDatabase database(out, 7005001, company2);
        CHECK(database.id == 7005001);
        CHECK(database.company == company2);
        CHECK(database.getGamesBeingTestedAmount() == 0);
        CHECK(database.getGamesWaitingForTestersAmount() == 0);
        CHECK(database.getTestRequestsAmount() == 0);
    }
    SECTION("Constructor - exceptions")
    {
        CHECK_THROWS_AS(TestingDatabase(out, 7000000, company), InvalidId);
        CHECK_THROWS_AS(TestingDatabase(out, 8000000, company), InvalidId);
    }
    SECTION("New requests creation")
    {
        database.newTestingRequest(game1);
        CHECK(database.id == 7000001);
        CHECK(database.company == company);
        CHECK(database.getGamesBeingTestedAmount() == 0);
        CHECK(database.getGamesWaitingForTestersAmount() == 0);
        CHECK(database.getTestRequestsAmount() == 1);

        database.newTestingRequest(game2);
        CHECK(database.id == 7000001);
        CHECK(database.company == company);
        CHECK(database.getGamesBeingTestedAmount() == 0);
        CHECK(database.getGamesWaitingForTestersAmount() == 0);
        CHECK(database.getTestRequestsAmount() == 2);
    }
    SECTION("Advancing requests")
    {
        database.newTestingRequest(game1);
        database.newTestingRequest(game2);
        CHECK(database.id == 7000001);
        CHECK(database.company == company);
        CHECK(database.getGamesBeingTestedAmount() == 0);
        CHECK(database.getGamesWaitingForTestersAmount() == 0);
        CHECK(database.getTestRequestsAmount() == 2);

        database.advanceRequestHandling(10);
        CHECK(database.id == 7000001);
        CHECK(database.company == company);
        CHECK(database.getGamesBeingTestedAmount() == 0);
        CHECK(database.getGamesWaitingForTestersAmount() == 0);
        CHECK(database.getTestRequestsAmount() == 2);

        database.advanceRequestHandling(12);
        CHECK(database.id == 7000001);
        CHECK(database.company == company);
        CHECK(database.getGamesBeingTestedAmount() == 0);
        CHECK(database.getGamesWaitingForTestersAmount() == 1);
        CHECK(database.getTestRequestsAmount() == 1);

        database.advanceRequestHandling(19);
        CHECK(database.id == 7000001);
        CHECK(database.company == company);
        CHECK(database.getGamesBeingTestedAmount() == 0);
        CHECK(database.getGamesWaitingForTestersAmount() == 1);
        CHECK(database.getTestRequestsAmount() == 1);

        database.advanceRequestHandling(1);
        CHECK(database.id == 7000001);
        CHECK(database.company == company);
        CHECK(database.getGamesBeingTestedAmount() == 0);
        CHECK(database.getGamesWaitingForTestersAmount() == 2);
        CHECK(database.getTestRequestsAmount() == 0);
    }
}


TEST_CASE("Assigning testers and removing testers to and from games", "[TestingDatabase]")
{
    TestingCompany company;
    OutputHandler out;
    TestingDatabase database(out, 7000001, company);
    Simulation sim;
    TestingCompany tcom;
    Producer pr(out, 14000001, "Pr", Address("SN", 2, 5, "SNville", "12-345"), sim, tcom);
    Game game1(1000001, "G", pr, 100, AbstractGame::Average, 1, true, Price(500));
    RolePlayingGame game2(3000001, "G2", pr, 100, AbstractGame::Complex, 2, 120, 240, true, Price(4000));
    auto tester1 = std::make_shared<Tester>(10000001, "Paweł", "Piekarski", 3);
    auto tester2 = std::make_shared<Tester>(10000001, "Paweł", "Piekarski", 4);
    auto tester3 = std::make_shared<Tester>(10000001, "Paweł", "Piekarski", 5);
    auto tester4 = std::make_shared<Tester>(10000001, "Paweł", "Piekarski", 6);
    auto tester5 = std::make_shared<Tester>(10000001, "Paweł", "Piekarski", 7);
    auto tester6 = std::make_shared<Tester>(10000001, "Paweł", "Piekarski", 8);
    auto tester7 = std::make_shared<Tester>(10000001, "Paweł", "Piekarski", 9);
    database.newTestingRequest(game1);
    database.newTestingRequest(game2);
    database.advanceRequestHandling(20);
    database.advanceRequestHandling(20);
    CHECK(database.getGamesBeingTestedAmount() == 0);
    CHECK(database.getGamesWaitingForTestersAmount() == 2);
    CHECK(database.getTestRequestsAmount() == 0);

    CHECK(database.assignTester(tester1));
    CHECK(database.getGamesBeingTestedAmount() == 1);
    CHECK(database.getGamesWaitingForTestersAmount() == 1);
    CHECK(database.getTestRequestsAmount() == 0);
    CHECK(tester1->getBusy());
    CHECK(tester1->getTestedGameRecord()->game == game1);

    CHECK(database.assignTester(tester2));
    CHECK(database.getGamesBeingTestedAmount() == 1);
    CHECK(database.getGamesWaitingForTestersAmount() == 1);
    CHECK(database.getTestRequestsAmount() == 0);
    CHECK(tester2->getBusy());
    CHECK(tester2->getTestedGameRecord()->game == game2);

    CHECK(database.assignTester(tester3));
    CHECK(database.getGamesBeingTestedAmount() == 2);
    CHECK(database.getGamesWaitingForTestersAmount() == 0);
    CHECK(database.getTestRequestsAmount() == 0);
    CHECK(tester3->getBusy());
    CHECK(tester3->getTestedGameRecord()->game == game2);

    CHECK(database.assignTester(tester4));
    CHECK(database.getGamesBeingTestedAmount() == 2);
    CHECK(database.getGamesWaitingForTestersAmount() == 0);
    CHECK(database.getTestRequestsAmount() == 0);
    CHECK(tester4->getBusy());
    CHECK(tester4->getTestedGameRecord()->game == game1);

    CHECK(database.assignTester(tester5));
    CHECK(database.getGamesBeingTestedAmount() == 2);
    CHECK(database.getGamesWaitingForTestersAmount() == 0);
    CHECK(database.getTestRequestsAmount() == 0);
    CHECK(tester5->getBusy());
    CHECK(tester5->getTestedGameRecord()->game == game2);

    CHECK(database.assignTester(tester6));
    CHECK(database.getGamesBeingTestedAmount() == 2);
    CHECK(database.getGamesWaitingForTestersAmount() == 0);
    CHECK(database.getTestRequestsAmount() == 0);
    CHECK(tester6->getBusy());
    CHECK(tester6->getTestedGameRecord()->game == game2);

    CHECK_FALSE(database.assignTester(tester7));
    CHECK(database.getGamesBeingTestedAmount() == 2);
    CHECK(database.getGamesWaitingForTestersAmount() == 0);
    CHECK(database.getTestRequestsAmount() == 0);
    CHECK_FALSE(tester7->getBusy());
    CHECK(tester7->getTestedGameRecord() == nullptr);

    SECTION("Remove testers from game2 until it stops being tested")
    {
        tester6->getTestedGameRecord()->removeTester(tester6);
        database.checkRecords();
        CHECK(database.getGamesBeingTestedAmount() == 2);
        CHECK(database.getGamesWaitingForTestersAmount() == 0);
        CHECK(database.getTestRequestsAmount() == 0);

        tester5->getTestedGameRecord()->removeTester(tester5);
        database.checkRecords();
        CHECK(database.getGamesBeingTestedAmount() == 2);
        CHECK(database.getGamesWaitingForTestersAmount() == 0);
        CHECK(database.getTestRequestsAmount() == 0);

        tester3->getTestedGameRecord()->removeTester(tester3);
        database.checkRecords();
        CHECK(database.getGamesBeingTestedAmount() == 1);
        CHECK(database.getGamesWaitingForTestersAmount() == 1);
        CHECK(database.getTestRequestsAmount() == 0);
    }

    SECTION("Check ending of testing")
    {
        tester1->getTestedGameRecord()->advanceTesting(400);
        database.checkRecords();
        CHECK_FALSE(tester1->getBusy());
        CHECK(tester1->getTestedGameRecord() == nullptr);
        CHECK_FALSE(tester4->getBusy());
        CHECK(tester4->getTestedGameRecord() == nullptr);
        CHECK(database.getGamesBeingTestedAmount() == 1);
        CHECK(database.getGamesWaitingForTestersAmount() == 0);
        CHECK(database.getTestRequestsAmount() == 0);
    }

    SECTION("<< operator")
    {
        std::stringstream stream1, stream2;
        stream1 << database;
        stream2 << "TestingDatabase 1";
        CHECK(stream1.str() == stream2.str());

        TestingDatabase database2(out, 7009000, company);
        stream1.str("");
        stream1.clear();
        stream2.str("");
        stream2.clear();

        stream1 << database2;
        stream2 << "TestingDatabase 9000";
        CHECK(stream1.str() == stream2.str());
    }
}