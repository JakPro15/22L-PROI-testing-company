#include "catch.hpp"
#include "../producer/producerdatabase.h"
#include "../producer/producer.h"
#include "../testingcompany/testingcompany.h"
#include "../simulation/simulation.h"
#include "../games/game.h"
#include "../exceptions.h"
#include <sstream>


TEST_CASE("ProducerDatabase methods", "[ProducerDatabase]")
{
    Simulation sim(3, 0, "../producers.txt", "../games.txt", "../testers.txt", "../managers.txt", "../simulationlog.txt");
    OutputHandler out("../simulationlog.txt");
    TestingCompany tcom(out);
    Producer pr(out, 14000001, "Pr", Address("SN", 2, 5, "SNville", "12-345"), sim, tcom);
    ProducerDatabase database(out, 12000001, pr);
    Game game(1000001, "Game", pr, 100, AbstractGame::Average, 3);
    SECTION("Constructor - typical")
    {
        CHECK(database.id == 12000001);
        CHECK(database.producer == pr);
        CHECK(database.getUntestedGamesAmount() == 0);

        Producer pr2(out, 14000002, "Pr", Address("SN", 2, 5, "SNville", "12-345"), sim, tcom);
        ProducerDatabase database2(out, 12999999, pr2);
        CHECK(database2.id == 12999999);
        CHECK(database2.producer == pr2);
        CHECK(database2.getUntestedGamesAmount() == 0);
    }
    SECTION("Constructor - exceptions")
    {
        CHECK_THROWS_AS(ProducerDatabase(out, 12000000, pr), InvalidId);
        CHECK_THROWS_AS(ProducerDatabase(out, 13000000, pr), InvalidId);
    }
    SECTION("Adding games - typical")
    {
        database.addGame(game);
        CHECK(database.id == 12000001);
        CHECK(database.producer == pr);
        CHECK(database.getUntestedGamesAmount() == 1);

        Game game2(1000002, "Game", pr, 100, AbstractGame::Average, 3);
        database.addGame(game2);
        CHECK(database.id == 12000001);
        CHECK(database.producer == pr);
        CHECK(database.getUntestedGamesAmount() == 2);
    }
    SECTION("Adding games - exceptions")
    {
        database.addGame(game);
        CHECK_THROWS_AS(database.addGame(game), DuplicateGameError);

        Producer pr2(out, 14000002, "Pr", Address("SN", 2, 5, "SNville", "12-345"), sim, tcom);
        Game game2(1000002, "Game", pr2, 100, AbstractGame::Average, 3);
        CHECK_THROWS_AS(database.addGame(game2), InvalidProducer);
    }
    // ProducerDatabase::checkPayments not tested here - its changes are not visible to the outside world,
    // except for Producer class
    // As such it will be tested alongside Producer methods.
    SECTION("getGameToBeTested")
    {
        CHECK(database.getUntestedGamesAmount() == 0);

        database.addGame(game);
        CHECK(database.getUntestedGamesAmount() == 1);

        Game game2(1000002, "Game", pr, 100, AbstractGame::Average, 3);
        database.addGame(game2);
        CHECK(database.getUntestedGamesAmount() == 2);

        CHECK(database.getGameToBeTested() == game);
        CHECK(database.getUntestedGamesAmount() == 1);

        CHECK(database.getGameToBeTested() == game2);
        CHECK(database.getUntestedGamesAmount() == 0);

        CHECK_THROWS_AS(database.getGameToBeTested(), NoGamesUntestedError);

        Game game3(1000003, "Game", pr, 100, AbstractGame::Average, 3);
        database.addGame(game3);
        CHECK(database.getUntestedGamesAmount() == 1);

        CHECK(database.getGameToBeTested() == game3);
        CHECK(database.getUntestedGamesAmount() == 0);

        CHECK_THROWS_AS(database.getGameToBeTested(), NoGamesUntestedError);
    }
    SECTION("gameFinishedTesting")
    {
        database.addGame(game);
        CHECK_THROWS_AS(database.gameFinishedTesting(game, 0), GameNotRequestedError);

        database.getGameToBeTested();
        CHECK_NOTHROW(database.gameFinishedTesting(game, 0));

        CHECK_THROWS_AS(database.gameFinishedTesting(game, 0), GameAlreadyTestedError);

        Game game2(1000003, "Game", pr, 100, AbstractGame::Average, 3);
        CHECK_THROWS_AS(database.gameFinishedTesting(game2, 0), GameNotPresentError);

        database.addGame(game2);
        CHECK_THROWS_AS(database.gameFinishedTesting(game2, 0), GameNotRequestedError);

        database.getGameToBeTested();
        CHECK_NOTHROW(database.gameFinishedTesting(game2, 0));

        CHECK_THROWS_AS(database.gameFinishedTesting(game2, 0), GameAlreadyTestedError);
    }
    SECTION("<< operator")
    {
        std::stringstream stream1, stream2;
        stream1 << database;
        stream2 << "ProducerDatabase 1";
        CHECK(stream1.str() == stream2.str());

        ProducerDatabase database2(out, 12009000, pr);
        stream1.str("");
        stream1.clear();
        stream2.str("");
        stream2.clear();

        stream1 << database2;
        stream2 << "ProducerDatabase 9000";
        CHECK(stream1.str() == stream2.str());
    }
}