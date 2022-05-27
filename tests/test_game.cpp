#include "catch.hpp"
#include "../games/game.h"
#include "../producer/producer.h"
#include "../testingcompany/testingcompany.h"
#include "../simulation/simulation.h"
#include "../exceptions.h"
#include <sstream>


TEST_CASE("Game methods", "[Game]")
{
    Simulation sim;
    TestingCompany tcom;
    OutputHandler out("../simulationlog.txt");
    Producer pr(out, 14000001, "Pr", Address("SN", 2, 5, "SNville", "12-345"), sim, tcom);
    Game game(1000001, "G", pr, 100, AbstractGame::Average, 3, true, Price(500));
    SECTION("Constructors and getters - typical")
    {
        // Construction from Price object
        Game game1(1000001, "G", pr, 100, AbstractGame::Average, 3, true, Price(500));
        CHECK(game1.id == 1000001);
        CHECK(game1.getTitle() == "G");
        CHECK(game1.producer == pr);
        CHECK(game1.getFilesSize() == 100);
        CHECK(game1.getComplexity() == 1);
        CHECK(game1.getCodeAvailable());
        CHECK(game1.getMarketPrice() == Price(5, 0));
        CHECK(game1.getMinTestersAmount() == 3);

        // Construction from one integer
        Game game2(1999999, "            TYYY", pr, 10000, AbstractGame::Complex, 1, false, 500);
        CHECK(game2.id == 1999999);
        CHECK(game2.getTitle() == "            TYYY");
        CHECK(game2.producer == pr);
        CHECK(game2.getFilesSize() == 10000);
        CHECK(game2.getComplexity() == 2);
        CHECK_FALSE(game2.getCodeAvailable());
        CHECK(game2.getMarketPrice() == Price(5, 0));
        CHECK(game2.getMinTestersAmount() == 1);

        // Construction from two integers
        Game game3(1000001, "G a a", pr, 234, AbstractGame::Simple, 23, true, 5, 12);
        CHECK(game3.id == 1000001);
        CHECK(game3.getTitle() == "G a a");
        CHECK(game3.producer == pr);
        CHECK(game3.getFilesSize() == 234);
        CHECK(game3.getComplexity() == 0);
        CHECK(game3.getCodeAvailable());
        CHECK(game3.getMarketPrice() == Price(512));
        CHECK(game3.getMinTestersAmount() == 23);
    }
    SECTION("Constructors - exceptions")
    {
        CHECK_THROWS_AS(Game(1000000, "G", pr, 100, AbstractGame::Average, 3, true, Price(500)), InvalidId);
        CHECK_THROWS_AS(Game(1000000, "G", pr, 100, AbstractGame::Average, 3, true, Price(500)), InvalidId);
        CHECK_THROWS_AS(Game(2000000, "G", pr, 100, AbstractGame::Average, 3, true, 5, 0), InvalidId);
        CHECK_THROWS_AS(Game(2000000, "G", pr, 100, AbstractGame::Average, 3, true, 5, 0), InvalidId);

        CHECK_THROWS_AS(Game(1000001, "", pr, 100, AbstractGame::Average, 3, true, Price(500)), InvalidTitle);
        CHECK_THROWS_AS(Game(1000001, "  ", pr, 100, AbstractGame::Average, 3, true, Price(500)), InvalidTitle);
        CHECK_THROWS_AS(Game(1000001, "\t\v", pr, 100, AbstractGame::Average, 3, true, Price(500)), InvalidTitle);
        CHECK_THROWS_AS(Game(1000001, "", pr, 100, AbstractGame::Average, 3, true, 5, 0), InvalidTitle);
        CHECK_THROWS_AS(Game(1000001, "  ", pr, 100, AbstractGame::Average, 3, true, 5, 0), InvalidTitle);
        CHECK_THROWS_AS(Game(1000001, "\t\v", pr, 100, AbstractGame::Average, 3, true, 5, 0), InvalidTitle);

        CHECK_THROWS_AS(Game(1000001, "G", pr, 0, AbstractGame::Average, 3, true, Price(500)), InvalidFilesSize);
        CHECK_THROWS_AS(Game(1000001, "G", pr, 0, AbstractGame::Average, 3, true, 5, 0), InvalidFilesSize);

        CHECK_THROWS_AS(Game(1000001, "G", pr, 100, AbstractGame::Average, 0, true, Price(500)), InvalidTestersAmount);
        CHECK_THROWS_AS(Game(1000001, "G", pr, 100, AbstractGame::Average, 0, true, 5, 0), InvalidTestersAmount);

        CHECK_THROWS_AS(Game(1000001, "G", pr, 100, AbstractGame::Average, 3, true, Price(-1)), InvalidPrice);
        CHECK_THROWS_AS(Game(1000001, "G", pr, 100, AbstractGame::Average, 3, true, -10), InvalidPrice);
        CHECK_THROWS_AS(Game(1000001, "G", pr, 100, AbstractGame::Average, 3, true, 5, -1), InvalidPrice);
        CHECK_THROWS_AS(Game(1000001, "G", pr, 100, AbstractGame::Average, 3, true, -1, 0), InvalidPrice);
        CHECK_THROWS_AS(Game(1000001, "G", pr, 100, AbstractGame::Average, 3, true, -2, 150), InvalidPrice);
    }
    SECTION("Title setter - typical")
    {
        game.setTitle("ABC");
        CHECK(game.id == 1000001);
        CHECK(game.getTitle() == "ABC");
        CHECK(game.producer == pr);
        CHECK(game.getFilesSize() == 100);
        CHECK(game.getComplexity() == 1);
        CHECK(game.getCodeAvailable());
        CHECK(game.getMarketPrice() == Price(5, 0));
        CHECK(game.getMinTestersAmount() == 3);

        game.setTitle("Specje \tu Sa");
        CHECK(game.id == 1000001);
        CHECK(game.getTitle() == "Specje \tu Sa");
        CHECK(game.producer == pr);
        CHECK(game.getFilesSize() == 100);
        CHECK(game.getComplexity() == 1);
        CHECK(game.getCodeAvailable());
        CHECK(game.getMarketPrice() == Price(5, 0));
        CHECK(game.getMinTestersAmount() == 3);
    }
    SECTION("Title setter - exceptions")
    {
        CHECK_THROWS_AS(game.setTitle(""), InvalidTitle);
        CHECK_THROWS_AS(game.setTitle("   "), InvalidTitle);
        CHECK_THROWS_AS(game.setTitle("\r\n\t \v"), InvalidTitle);
    }
    SECTION("Files size setter - typical")
    {
        game.setFilesSize(234);
        CHECK(game.id == 1000001);
        CHECK(game.getTitle() == "G");
        CHECK(game.producer == pr);
        CHECK(game.getFilesSize() == 234);
        CHECK(game.getComplexity() == 1);
        CHECK(game.getCodeAvailable());
        CHECK(game.getMarketPrice() == Price(5, 0));
        CHECK(game.getMinTestersAmount() == 3);

        game.setFilesSize(734);
        CHECK(game.id == 1000001);
        CHECK(game.getTitle() == "G");
        CHECK(game.producer == pr);
        CHECK(game.getFilesSize() == 734);
        CHECK(game.getComplexity() == 1);
        CHECK(game.getCodeAvailable());
        CHECK(game.getMarketPrice() == Price(5, 0));
        CHECK(game.getMinTestersAmount() == 3);
    }
    SECTION("Files size setter - exception")
    {
        CHECK_THROWS_AS(game.setFilesSize(0), InvalidFilesSize);
    }
    SECTION("Code available setter")
    {
        game.setCodeAvailable(true);
        CHECK(game.id == 1000001);
        CHECK(game.getTitle() == "G");
        CHECK(game.producer == pr);
        CHECK(game.getFilesSize() == 100);
        CHECK(game.getComplexity() == 1);
        CHECK(game.getCodeAvailable());
        CHECK(game.getMarketPrice() == Price(5, 0));
        CHECK(game.getMinTestersAmount() == 3);

        game.setCodeAvailable(false);
        CHECK(game.id == 1000001);
        CHECK(game.getTitle() == "G");
        CHECK(game.producer == pr);
        CHECK(game.getFilesSize() == 100);
        CHECK(game.getComplexity() == 1);
        CHECK_FALSE(game.getCodeAvailable());
        CHECK(game.getMarketPrice() == Price(5, 0));
        CHECK(game.getMinTestersAmount() == 3);
    }
    SECTION("Complexity setter")
    {
        game.setComplexity(AbstractGame::Simple);
        CHECK(game.id == 1000001);
        CHECK(game.getTitle() == "G");
        CHECK(game.producer == pr);
        CHECK(game.getFilesSize() == 100);
        CHECK(game.getComplexity() == 0);
        CHECK(game.getCodeAvailable());
        CHECK(game.getMarketPrice() == Price(5, 0));
        CHECK(game.getMinTestersAmount() == 3);

        game.setComplexity(AbstractGame::Complex);
        CHECK(game.id == 1000001);
        CHECK(game.getTitle() == "G");
        CHECK(game.producer == pr);
        CHECK(game.getFilesSize() == 100);
        CHECK(game.getComplexity() == 2);
        CHECK(game.getCodeAvailable());
        CHECK(game.getMarketPrice() == Price(5, 0));
        CHECK(game.getMinTestersAmount() == 3);
    }
    SECTION("MinTestersAmount setter - typical")
    {
        game.setMinTestersAmount(1);
        CHECK(game.id == 1000001);
        CHECK(game.getTitle() == "G");
        CHECK(game.producer == pr);
        CHECK(game.getFilesSize() == 100);
        CHECK(game.getComplexity() == 1);
        CHECK(game.getCodeAvailable());
        CHECK(game.getMarketPrice() == Price(5, 0));
        CHECK(game.getMinTestersAmount() == 1);

        game.setMinTestersAmount(734);
        CHECK(game.id == 1000001);
        CHECK(game.getTitle() == "G");
        CHECK(game.producer == pr);
        CHECK(game.getFilesSize() == 100);
        CHECK(game.getComplexity() == 1);
        CHECK(game.getCodeAvailable());
        CHECK(game.getMarketPrice() == Price(5, 0));
        CHECK(game.getMinTestersAmount() == 734);
    }
    SECTION("MinTestersAmount setter - exception")
    {
        CHECK_THROWS_AS(game.setMinTestersAmount(0), InvalidTestersAmount);
    }
    SECTION("Market price setter 1 - typical")
    {
        game.setMarketPrice(Price(20, 12));
        CHECK(game.id == 1000001);
        CHECK(game.getTitle() == "G");
        CHECK(game.producer == pr);
        CHECK(game.getFilesSize() == 100);
        CHECK(game.getComplexity() == 1);
        CHECK(game.getCodeAvailable());
        CHECK(game.getMarketPrice() == Price(20, 12));
        CHECK(game.getMinTestersAmount() == 3);

        game.setMarketPrice(734);
        CHECK(game.id == 1000001);
        CHECK(game.getTitle() == "G");
        CHECK(game.producer == pr);
        CHECK(game.getFilesSize() == 100);
        CHECK(game.getComplexity() == 1);
        CHECK(game.getCodeAvailable());
        CHECK(game.getMarketPrice() == Price(7, 34));
        CHECK(game.getMinTestersAmount() == 3);
    }
    SECTION("Market price setter 2 - typical")
    {
        game.setMarketPrice(234, 0);
        CHECK(game.id == 1000001);
        CHECK(game.getTitle() == "G");
        CHECK(game.producer == pr);
        CHECK(game.getFilesSize() == 100);
        CHECK(game.getComplexity() == 1);
        CHECK(game.getCodeAvailable());
        CHECK(game.getMarketPrice() == Price(234, 0));
        CHECK(game.getMinTestersAmount() == 3);

        game.setMarketPrice(0, 120);
        CHECK(game.id == 1000001);
        CHECK(game.getTitle() == "G");
        CHECK(game.producer == pr);
        CHECK(game.getFilesSize() == 100);
        CHECK(game.getComplexity() == 1);
        CHECK(game.getCodeAvailable());
        CHECK(game.getMarketPrice() == Price(1, 20));
        CHECK(game.getMinTestersAmount() == 3);
    }
    SECTION("Market price setters - exceptions")
    {
        CHECK_THROWS_AS(game.setMarketPrice(-1), InvalidPrice);
        CHECK_THROWS_AS(game.setMarketPrice(-1, 0), InvalidPrice);
        CHECK_THROWS_AS(game.setMarketPrice(0, -1), InvalidPrice);
        CHECK_THROWS_AS(game.setMarketPrice(-20, 300), InvalidPrice);
    }
    SECTION("Time of testing")
    {
        game.setFilesSize(100000);
        CHECK(game.getTestingTime() == 20);
        game.setFilesSize(200000);
        CHECK(game.getTestingTime() == 39);
        game.setCodeAvailable(false);
        CHECK(game.getTestingTime() == 48);
        game.setComplexity(AbstractGame::Simple);
        CHECK(game.getTestingTime() == 40);
        game.setMinTestersAmount(15);
        CHECK(game.getTestingTime() == 48);
    }
    SECTION("Price of testing")
    {
        game.setFilesSize(100000);
        CHECK(game.getTestingPrice() == Price(800, 0));
        game.setFilesSize(200000);
        CHECK(game.getTestingPrice() == Price(1560, 0));
        game.setCodeAvailable(false);
        CHECK(game.getTestingPrice() == Price(1920, 0));
        game.setComplexity(AbstractGame::Simple);
        CHECK(game.getTestingPrice() == Price(1600, 0));
        game.setMinTestersAmount(15);
        CHECK(game.getTestingPrice() == Price(1920, 0));
        game.setMinTestersAmount(9);
        game.setMarketPrice(0);
        CHECK(game.getTestingPrice() == Price(1280, 0));
        game.setMarketPrice(Price(110, 0));
        CHECK(game.getTestingPrice() == Price(1680, 0));
        game.setMarketPrice(Price(200, 0));
        CHECK(game.getTestingPrice() == Price(2400, 0));
    }
    SECTION("<< operator")
    {
        std::stringstream stream1, stream2;
        stream1 << game;
        stream2 << "Game 1";
        CHECK(stream1.str() == stream2.str());

        Game game1(1009000, "G", pr, 100, AbstractGame::Average, 3, true, Price(500));
        stream1.str("");
        stream1.clear();
        stream2.str("");
        stream2.clear();

        stream1 << game1;
        stream2 << "Game 9000";
        CHECK(stream1.str() == stream2.str());
    }
    SECTION("Equality operators")
    {
        Game &game2 = game;
        CHECK(game == game2);
        CHECK_FALSE(game != game2);
        game.setTitle("ABCD");
        CHECK(game2 == game);
        CHECK_FALSE(game != game2);

        Game game1(1009000, "G", pr, 100, AbstractGame::Average, 3, true, Price(500));
        CHECK_FALSE(game == game1);
        CHECK(game != game1);
        CHECK_FALSE(game1 == game2);
        CHECK(game1 != game2);
    }
}
