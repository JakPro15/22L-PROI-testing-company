#include "catch.hpp"
#include "../testingcompany/testingrecord.h"
#include "../testingcompany/tester.h"
#include "../games/game.h"
#include "../producer/producer.h"
#include "../testingcompany/testingcompany.h"
#include "../simulation/simulation.h"
#include "../exceptions.h"
#include <sstream>


TEST_CASE("TestingRecord constructor and setters", "[TestingRecord]")
{
    Simulation sim;
    TestingCompany tcom;
    OutputHandler out;
    Producer pr(out, 14000001, "Pr", Address("SN", 2, 5, "SNville", "12-345"), sim, tcom);
    Game game(1000001, "G", pr, 100000, AbstractGame::Average, 3, true, Price(500));
    TestingRecord record(out, 6000001, game, 5);
    SECTION("Constructor (typical) and getters")
    {
        CHECK(record.id == 6000001);
        CHECK_FALSE(record.getBeingTested());
        CHECK(record.game == game);
        CHECK(record.getMinTestersAmount() == 3);
        CHECK(record.getMaxTestersAmount() == 5);
        CHECK(record.getTesters() == std::list<std::shared_ptr<Tester>>());

        TestingRecord record2(out, 6500000, game, 5);
        CHECK(record2.id == 6500000);
        CHECK_FALSE(record.getBeingTested());
        CHECK(record2.game == game);
        CHECK(record2.getMinTestersAmount() == 3);
        CHECK(record2.getMaxTestersAmount() == 5);
        CHECK(record2.getTesters() == std::list<std::shared_ptr<Tester>>());

        Game game2(1000002, "G", pr, 100, AbstractGame::Average, 30, true, Price(500));
        TestingRecord record3(out, 6500001, game2);
        CHECK(record3.id == 6500001);
        CHECK_FALSE(record.getBeingTested());
        CHECK(record3.game == game2);
        CHECK(record3.getMinTestersAmount() == 30);
        CHECK(record3.getMaxTestersAmount() == 60);
        CHECK(record3.getTesters() == std::list<std::shared_ptr<Tester>>());
    }
    SECTION("Constructor - exceptions")
    {
        CHECK_THROWS_AS(TestingRecord(out, 6000000, game, 200), InvalidId);
        CHECK_THROWS_AS(TestingRecord(out, 7000000, game, 200), InvalidId);
        CHECK_THROWS_AS(TestingRecord(out, 6000000, game), InvalidId);
        CHECK_THROWS_AS(TestingRecord(out, 7000000, game), InvalidId);

        CHECK_THROWS_AS(TestingRecord(out, 6000001, game, 2), InvalidTestersAmount);
    }
    SECTION("Testers collection methods")
    {
        std::shared_ptr<Tester> tester1Ptr = std::make_shared<Tester>(10000001, "Paweł", "Piekarski", 5);
        std::shared_ptr<Tester> tester2Ptr = std::make_shared<Tester>(10000001, "Paweł", "Piekarski", 5);
        std::shared_ptr<Tester> tester3Ptr = std::make_shared<Tester>(10000001, "Paweł", "Piekarski", 5);
        std::shared_ptr<Tester> tester4Ptr = std::make_shared<Tester>(10000001, "Paweł", "Piekarski", 5);
        std::shared_ptr<Tester> tester5Ptr = std::make_shared<Tester>(10000001, "Paweł", "Piekarski", 5);
        std::shared_ptr<Tester> tester6Ptr = std::make_shared<Tester>(10000001, "Paweł", "Piekarski", 5);

        std::list<std::shared_ptr<Tester>> testersPtrs = {};
        testersPtrs.push_back(tester1Ptr);
        record.addTester(tester1Ptr);
        CHECK(record.getTesters() == testersPtrs);
        CHECK_FALSE(record.getBeingTested());
        CHECK(tester1Ptr->getBusy());
        CHECK(tester1Ptr->getTestedGameRecord() == &record);

        testersPtrs.push_back(tester2Ptr);
        record.addTester(tester2Ptr);
        CHECK(record.getTesters() == testersPtrs);
        CHECK_FALSE(record.getBeingTested());
        CHECK(tester2Ptr->getBusy());
        CHECK(tester2Ptr->getTestedGameRecord() == &record);

        record.addTester(tester2Ptr);
        CHECK(record.getTesters() == testersPtrs);
        CHECK_FALSE(record.getBeingTested());
        CHECK(tester2Ptr->getBusy());
        CHECK(tester2Ptr->getTestedGameRecord() == &record);

        testersPtrs.push_back(tester3Ptr);
        record.addTester(tester3Ptr);
        CHECK(record.getTesters() == testersPtrs);
        CHECK(record.getBeingTested());
        CHECK(tester3Ptr->getBusy());
        CHECK(tester3Ptr->getTestedGameRecord() == &record);

        testersPtrs.push_back(tester4Ptr);
        record.addTester(tester4Ptr);
        CHECK(record.getTesters() == testersPtrs);
        CHECK(record.getBeingTested());
        CHECK(tester4Ptr->getBusy());
        CHECK(tester4Ptr->getTestedGameRecord() == &record);

        testersPtrs.push_back(tester5Ptr);
        record.addTester(tester5Ptr);
        CHECK(record.getTesters() == testersPtrs);
        CHECK(record.getBeingTested());
        CHECK(tester5Ptr->getBusy());
        CHECK(tester5Ptr->getTestedGameRecord() == &record);

        record.addTester(tester6Ptr);
        CHECK(record.getTesters() == testersPtrs);
        CHECK(record.getBeingTested());
        CHECK_FALSE(tester6Ptr->getBusy());
        CHECK(tester6Ptr->getTestedGameRecord() == nullptr);

        testersPtrs.remove(tester2Ptr);
        record.removeTester(tester2Ptr);
        CHECK(record.getTesters() == testersPtrs);
        CHECK(record.getBeingTested());
        CHECK_FALSE(tester2Ptr->getBusy());
        CHECK(tester2Ptr->getTestedGameRecord() == nullptr);

        testersPtrs.remove(tester5Ptr);
        record.removeTester(tester5Ptr);
        CHECK(record.getTesters() == testersPtrs);
        CHECK(record.getBeingTested());
        CHECK_FALSE(tester5Ptr->getBusy());
        CHECK(tester5Ptr->getTestedGameRecord() == nullptr);

        record.removeTester(tester5Ptr);
        CHECK(record.getTesters() == testersPtrs);
        CHECK(record.getBeingTested());
        CHECK_FALSE(tester5Ptr->getBusy());
        CHECK(tester5Ptr->getTestedGameRecord() == nullptr);

        testersPtrs.remove(tester4Ptr);
        record.removeTester(tester4Ptr);
        CHECK(record.getTesters() == testersPtrs);
        CHECK_FALSE(record.getBeingTested());
        CHECK_FALSE(tester4Ptr->getBusy());
        CHECK(tester4Ptr->getTestedGameRecord() == nullptr);
    }
    SECTION("Exceptions")
    {
        Game game(1000001, "G", pr, 100, AbstractGame::Average, 3, true, Price(500));
        TestingRecord record(out, 6000001, game, 5);

        std::shared_ptr<Tester> tester1Ptr = std::make_shared<Tester>(10000001, "Paweł", "Piekarski", 4);
        std::shared_ptr<Tester> tester2Ptr = std::make_shared<Tester>(10000001, "Paweł", "Piekarski", 5);
        std::shared_ptr<Tester> tester3Ptr = std::make_shared<Tester>(10000001, "Paweł", "Piekarski", 6);
        record.addTester(tester1Ptr);
        record.addTester(tester2Ptr);
        record.addTester(tester3Ptr);

        record.advanceTesting(30);
        CHECK(record.checkFinished());
        CHECK_THROWS_AS(record.addTester(tester1Ptr), TestingEndedError);
        CHECK_THROWS_AS(record.addTester(tester2Ptr), TestingEndedError);
        CHECK_THROWS_AS(record.removeTester(tester1Ptr), TestingEndedError);
    }
}


TEST_CASE("TestingRecord time advancing methods", "[TestingRecord]")
{
    std::srand(0);
    Simulation sim;
    TestingCompany tcom;
    OutputHandler out;
    Producer pr(out, 14000001, "Pr", Address("SN", 2, 5, "SNville", "12-345"), sim, tcom);

    SECTION("Case 1 - total effort == 30")
    {
        Game game(1000001, "G", pr, 100, AbstractGame::Average, 3, true, Price(500));
        TestingRecord record(out, 6000001, game, 5);

        std::shared_ptr<Tester> tester1Ptr = std::make_shared<Tester>(10000001, "Paweł", "Piekarski", 4);
        std::shared_ptr<Tester> tester2Ptr = std::make_shared<Tester>(10000001, "Paweł", "Piekarski", 5);
        std::shared_ptr<Tester> tester3Ptr = std::make_shared<Tester>(10000001, "Paweł", "Piekarski", 6);
        std::list<std::shared_ptr<Tester>> testerPtrs = {tester1Ptr, tester2Ptr, tester3Ptr};
        record.addTester(tester1Ptr);
        record.addTester(tester2Ptr);
        record.addTester(tester3Ptr);

        record.advanceTesting(12);
        CHECK_FALSE(record.checkFinished());
        CHECK(record.getBeingTested());
        CHECK(record.getTesters() == testerPtrs);
        CHECK(tester1Ptr->getBusy());
        CHECK(tester1Ptr->getTestedGameRecord() == &record);
        CHECK(tester2Ptr->getBusy());
        CHECK(tester2Ptr->getTestedGameRecord() == &record);
        CHECK(tester3Ptr->getBusy());
        CHECK(tester3Ptr->getTestedGameRecord() == &record);

        record.advanceTesting(12);
        CHECK_FALSE(record.checkFinished());
        CHECK(record.getBeingTested());
        CHECK(record.getTesters() == testerPtrs);
        CHECK(tester1Ptr->getBusy());
        CHECK(tester1Ptr->getTestedGameRecord() == &record);
        CHECK(tester2Ptr->getBusy());
        CHECK(tester2Ptr->getTestedGameRecord() == &record);
        CHECK(tester3Ptr->getBusy());
        CHECK(tester3Ptr->getTestedGameRecord() == &record);

        record.advanceTesting(12);
        CHECK(record.getTesters() == testerPtrs);
        CHECK(record.getBeingTested());
        CHECK(tester1Ptr->getBusy());
        CHECK(tester1Ptr->getTestedGameRecord() == &record);
        CHECK(tester2Ptr->getBusy());
        CHECK(tester2Ptr->getTestedGameRecord() == &record);
        CHECK(tester3Ptr->getBusy());
        CHECK(tester3Ptr->getTestedGameRecord() == &record);

        CHECK(record.checkFinished());
        CHECK_FALSE(record.getBeingTested());
        CHECK(record.getTesters() == std::list<std::shared_ptr<Tester>>());
        CHECK_FALSE(tester1Ptr->getBusy());
        CHECK(tester1Ptr->getTestedGameRecord() == nullptr);
        CHECK_FALSE(tester2Ptr->getBusy());
        CHECK(tester2Ptr->getTestedGameRecord() == nullptr);
        CHECK_FALSE(tester3Ptr->getBusy());
        CHECK(tester3Ptr->getTestedGameRecord() == nullptr);
    }
    SECTION("Case 2 - total effort == 45")
    {
        Game game(1000001, "G", pr, 10000, AbstractGame::Average, 3, true, Price(500));
        TestingRecord record(out, 6000001, game, 5);

        std::shared_ptr<Tester> tester1Ptr = std::make_shared<Tester>(10000001, "Paweł", "Piekarski", 4);
        std::shared_ptr<Tester> tester2Ptr = std::make_shared<Tester>(10000001, "Paweł", "Piekarski", 5);
        std::shared_ptr<Tester> tester3Ptr = std::make_shared<Tester>(10000001, "Paweł", "Piekarski", 6);
        std::list<std::shared_ptr<Tester>> testerPtrs = {tester1Ptr, tester2Ptr, tester3Ptr};
        record.addTester(tester1Ptr);
        record.addTester(tester2Ptr);
        record.addTester(tester3Ptr);

        record.advanceTesting(24);
        CHECK_FALSE(record.checkFinished());
        CHECK(record.getBeingTested());
        CHECK(record.getTesters() == testerPtrs);
        CHECK(tester1Ptr->getBusy());
        CHECK(tester1Ptr->getTestedGameRecord() == &record);
        CHECK(tester2Ptr->getBusy());
        CHECK(tester2Ptr->getTestedGameRecord() == &record);
        CHECK(tester3Ptr->getBusy());
        CHECK(tester3Ptr->getTestedGameRecord() == &record);

        record.advanceTesting(6);
        CHECK_FALSE(record.checkFinished());
        CHECK(record.getBeingTested());
        CHECK(record.getTesters() == testerPtrs);
        CHECK(tester1Ptr->getBusy());
        CHECK(tester1Ptr->getTestedGameRecord() == &record);
        CHECK(tester2Ptr->getBusy());
        CHECK(tester2Ptr->getTestedGameRecord() == &record);
        CHECK(tester3Ptr->getBusy());
        CHECK(tester3Ptr->getTestedGameRecord() == &record);

        record.advanceTesting(9);
        CHECK_FALSE(record.checkFinished());
        CHECK(record.getBeingTested());
        CHECK(record.getTesters() == testerPtrs);
        CHECK(tester1Ptr->getBusy());
        CHECK(tester1Ptr->getTestedGameRecord() == &record);
        CHECK(tester2Ptr->getBusy());
        CHECK(tester2Ptr->getTestedGameRecord() == &record);
        CHECK(tester3Ptr->getBusy());
        CHECK(tester3Ptr->getTestedGameRecord() == &record);

        record.advanceTesting(6);
        CHECK(record.checkFinished());
        CHECK_FALSE(record.getBeingTested());
        CHECK(record.getTesters() == std::list<std::shared_ptr<Tester>>());
        CHECK_FALSE(tester1Ptr->getBusy());
        CHECK(tester1Ptr->getTestedGameRecord() == nullptr);
        CHECK_FALSE(tester2Ptr->getBusy());
        CHECK(tester2Ptr->getTestedGameRecord() == nullptr);
        CHECK_FALSE(tester3Ptr->getBusy());
        CHECK(tester3Ptr->getTestedGameRecord() == nullptr);
    }
    SECTION("Exception")
    {
        Game game(1000001, "G", pr, 100, AbstractGame::Average, 3, true, Price(500));
        TestingRecord record(out, 6000001, game, 5);

        std::shared_ptr<Tester> tester1Ptr = std::make_shared<Tester>(10000001, "Paweł", "Piekarski", 4);
        std::shared_ptr<Tester> tester2Ptr = std::make_shared<Tester>(10000001, "Paweł", "Piekarski", 5);
        std::shared_ptr<Tester> tester3Ptr = std::make_shared<Tester>(10000001, "Paweł", "Piekarski", 6);
        std::list<std::shared_ptr<Tester>> testerPtrs = {tester1Ptr, tester2Ptr, tester3Ptr};
        record.addTester(tester1Ptr);
        record.addTester(tester2Ptr);
        record.addTester(tester3Ptr);

        record.advanceTesting(30);
        CHECK(record.checkFinished());
        CHECK_THROWS_AS(record.advanceTesting(2), TestingEndedError);
    }
}


TEST_CASE("TestingRecord total time and price methods", "[TestingRecord]")
{
    std::srand(0);
    Simulation sim;
    TestingCompany tcom;
    OutputHandler out;
    Producer pr(out, 14000001, "Pr", Address("SN", 2, 5, "SNville", "12-345"), sim, tcom);
    SECTION("Case 1 - total effort == 30, real time == 1")
    {
        Game game(1000001, "G", pr, 100, AbstractGame::Average, 3, true, Price(500));
        TestingRecord record(out, 6000001, game, 5);
        std::shared_ptr<Tester> tester1Ptr = std::make_shared<Tester>(10000001, "Paweł", "Piekarski", 4);
        std::shared_ptr<Tester> tester2Ptr = std::make_shared<Tester>(10000001, "Paweł", "Piekarski", 5);
        std::shared_ptr<Tester> tester3Ptr = std::make_shared<Tester>(10000001, "Paweł", "Piekarski", 6);
        record.addTester(tester1Ptr);
        record.addTester(tester2Ptr);
        record.addTester(tester3Ptr);

        record.advanceTesting(30);
        CHECK(record.checkFinished());
        CHECK(record.getRealTime() == 1);
        CHECK(record.getRealPrice() == game.getTestingPrice() * 2);
    }
    SECTION("Case 2 - total effort == 45, real time == 4")
    {
        Game game(1000001, "G", pr, 10000, AbstractGame::Average, 3, true, Price(500));
        TestingRecord record(out, 6000001, game, 5);
        std::shared_ptr<Tester> tester1Ptr = std::make_shared<Tester>(10000001, "Paweł", "Piekarski", 4);
        std::shared_ptr<Tester> tester2Ptr = std::make_shared<Tester>(10000001, "Paweł", "Piekarski", 5);
        std::shared_ptr<Tester> tester3Ptr = std::make_shared<Tester>(10000001, "Paweł", "Piekarski", 6);
        record.addTester(tester1Ptr);
        record.addTester(tester2Ptr);
        record.addTester(tester3Ptr);
        CHECK_FALSE(record.checkFinished());
        CHECK_FALSE(record.checkFinished());
        CHECK_FALSE(record.checkFinished());

        record.advanceTesting(45);
        CHECK(record.checkFinished());
        CHECK(record.getRealTime() == 4);
        CHECK(record.getRealPrice() == game.getTestingPrice() * 1.5 * 0.8);
    }
    SECTION("Exceptions")
    {
        Game game(1000001, "G", pr, 100, AbstractGame::Average, 3, true, Price(500));
        TestingRecord record(out, 6000001, game, 5);
        CHECK_THROWS_AS(record.getRealTime(), TestingNotEndedError);
        CHECK_THROWS_AS(record.getRealPrice(), TestingNotEndedError);
    }
}


TEST_CASE("Minor methods")
{
    Simulation sim;
    TestingCompany tcom;
    OutputHandler out;
    Producer pr(out, 14000001, "Pr", Address("SN", 2, 5, "SNville", "12-345"), sim, tcom);
    Game game(1000001, "G", pr, 100, AbstractGame::Average, 3, true, Price(500));
    TestingRecord record(out, 6000001, game, 5);
    SECTION("MaxTesterAmount setter - typical")
    {
        record.setMaxTestersAmount(12);
        CHECK(record.id == 6000001);
        CHECK_FALSE(record.getBeingTested());
        CHECK(record.game == game);
        CHECK(record.getMinTestersAmount() == 3);
        CHECK(record.getMaxTestersAmount() == 12);
        CHECK(record.getTesters() == std::list<std::shared_ptr<Tester>>());

        record.setMaxTestersAmount(3);
        CHECK(record.id == 6000001);
        CHECK_FALSE(record.getBeingTested());
        CHECK(record.game == game);
        CHECK(record.getMinTestersAmount() == 3);
        CHECK(record.getMaxTestersAmount() == 3);
        CHECK(record.getTesters() == std::list<std::shared_ptr<Tester>>());
    }
    SECTION("MaxTesterAmount setter - exceptions")
    {
        CHECK_THROWS_AS(record.setMaxTestersAmount(2), InvalidTestersAmount);
        CHECK_THROWS_AS(record.setMaxTestersAmount(0), InvalidTestersAmount);

        std::shared_ptr<Tester> tester1Ptr = std::make_shared<Tester>(10000001, "Paweł", "Piekarski", 4);
        std::shared_ptr<Tester> tester2Ptr = std::make_shared<Tester>(10000001, "Paweł", "Piekarski", 5);
        std::shared_ptr<Tester> tester3Ptr = std::make_shared<Tester>(10000001, "Paweł", "Piekarski", 6);
        record.addTester(tester1Ptr);
        record.addTester(tester2Ptr);
        record.addTester(tester3Ptr);

        record.advanceTesting(30);
        CHECK(record.checkFinished());
        CHECK_THROWS_AS(record.setMaxTestersAmount(45), TestingEndedError);
    }
    SECTION("<< operator")
    {
        std::stringstream stream1, stream2;
        stream1 << record;
        stream2 << "TestingRecord 1";
        CHECK(stream1.str() == stream2.str());

        stream1.str("");
        stream1.clear();
        stream2.str("");
        stream2.clear();

        TestingRecord record2(out, 6009011, game, 5);
        stream1 << record2;
        stream2 << "TestingRecord 9011";
        CHECK(stream1.str() == stream2.str());
    }
}