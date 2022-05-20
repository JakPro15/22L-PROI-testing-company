#include "catch.hpp"
#include "../producer/producerdatabase.h"
#include "../exceptions.h"
#include <sstream>


TEST_CASE("ProducerDatabase methods", "[ProducerDatabase]")
{
    Producer pr;
    ProducerDatabase database(12000001, pr);
    Game game(1000001, "Game", pr, 100, AbstractGame::Average, 3);
    SECTION("Constructor - typical")
    {
        CHECK(database.id == 12000001);
        CHECK(database.producer == pr);
        CHECK(database.getUntestedGamesAmount() == 0);

        Producer pr2;
        ProducerDatabase database2(12999999, pr2);
        CHECK(database2.id == 12999999);
        CHECK(database2.producer == pr2);
        CHECK(database2.getUntestedGamesAmount() == 0);
    }
    SECTION("Constructor - exceptions")
    {
        CHECK_THROWS_AS(ProducerDatabase(12000000, pr), InvalidId);
        CHECK_THROWS_AS(ProducerDatabase(13000000, pr), InvalidId);
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

        Producer pr2;
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
        CHECK_THROWS_AS(database.gameFinishedTesting(game), GameNotRequestedError);

        database.getGameToBeTested();
        CHECK_NOTHROW(database.gameFinishedTesting(game));

        CHECK_THROWS_AS(database.gameFinishedTesting(game), GameAlreadyTestedError);

        Game game2(1000003, "Game", pr, 100, AbstractGame::Average, 3);
        CHECK_THROWS_AS(database.gameFinishedTesting(game2), GameNotPresentError);

        database.addGame(game2);
        CHECK_THROWS_AS(database.gameFinishedTesting(game2), GameNotRequestedError);

        database.getGameToBeTested();
        CHECK_NOTHROW(database.gameFinishedTesting(game2));

        CHECK_THROWS_AS(database.gameFinishedTesting(game2), GameAlreadyTestedError);
    }
}