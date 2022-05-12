#include "catch.hpp"
#include "../infinitegame.h"
#include "../exceptions.h"
#include <sstream>


TEST_CASE("InfiniteGame methods", "[InfiniteGame]")
{
    Producer pr;
    InfiniteGame game(4000001, "G", pr, 100, AbstractGame::Average, 3, InfiniteGame::Average, true, Price(500));
    SECTION("Constructors and getters - typical")
    {
        // Construction from Price object
        InfiniteGame game1(4000001, "G", pr, 100, AbstractGame::Average, 3, InfiniteGame::Average, true, Price(500));
        CHECK(game1.getId() == 4000001);
        CHECK(game1.getTitle() == "G");
        CHECK(&game1.getProducer() == &pr);
        CHECK(game1.getFilesSize() == 100);
        CHECK(game1.getComplexity() == 1);
        CHECK(game1.getDepth() == 0);
        CHECK(game1.getCodeAvailable());
        CHECK(game1.getMarketPrice() == Price(5, 0));
        CHECK(game1.getMinTestersAmount() == 3);

        // Construction from one integer
        InfiniteGame game2(4999999, "            TYYY", pr, 10000, AbstractGame::Complex, 1, InfiniteGame::Shallow, false, 500);
        CHECK(game2.getId() == 4999999);
        CHECK(game2.getTitle() == "            TYYY");
        CHECK(&game2.getProducer() == &pr);
        CHECK(game2.getFilesSize() == 10000);
        CHECK(game2.getComplexity() == 2);
        CHECK(game2.getDepth() == -1);
        CHECK_FALSE(game2.getCodeAvailable());
        CHECK(game2.getMarketPrice() == Price(5, 0));
        CHECK(game2.getMinTestersAmount() == 1);

        // Construction from two integers
        InfiniteGame game3(4000001, "G a a", pr, 234, AbstractGame::Simple, 23, InfiniteGame::Expansive, true, 5, 12);
        CHECK(game3.getId() == 4000001);
        CHECK(game3.getTitle() == "G a a");
        CHECK(&game3.getProducer() == &pr);
        CHECK(game3.getFilesSize() == 234);
        CHECK(game3.getComplexity() == 0);
        CHECK(game3.getDepth() == 2);
        CHECK(game3.getCodeAvailable());
        CHECK(game3.getMarketPrice() == Price(512));
        CHECK(game3.getMinTestersAmount() == 23);
    }
    SECTION("Constructors - exceptions")
    {
        CHECK_THROWS_AS(
            InfiniteGame(4000000, "G", pr, 100, AbstractGame::Average, 3, InfiniteGame::Average, true, Price(500)), InvalidId
        );
        CHECK_THROWS_AS(
            InfiniteGame(4000000, "G", pr, 100, AbstractGame::Average, 3, InfiniteGame::Average, true, Price(500)), InvalidId
        );
        CHECK_THROWS_AS(
            InfiniteGame(5000000, "G", pr, 100, AbstractGame::Average, 3, InfiniteGame::Average, true, 5, 0), InvalidId
        );
        CHECK_THROWS_AS(
            InfiniteGame(5000000, "G", pr, 100, AbstractGame::Average, 3, InfiniteGame::Average, true, 5, 0), InvalidId
        );

        CHECK_THROWS_AS(
            InfiniteGame(4000001, "", pr, 100, AbstractGame::Average, 3, InfiniteGame::Average, true, Price(500)),
            InvalidTitle
        );
        CHECK_THROWS_AS(
            InfiniteGame(4000001, "  ", pr, 100, AbstractGame::Average, 3, InfiniteGame::Average, true, Price(500)),
            InvalidTitle
        );
        CHECK_THROWS_AS(
            InfiniteGame(4000001, "\t\v", pr, 100, AbstractGame::Average, 3, InfiniteGame::Average, true, Price(500)),
            InvalidTitle
        );
        CHECK_THROWS_AS(
            InfiniteGame(4000001, "", pr, 100, AbstractGame::Average, 3, InfiniteGame::Average, true, 5, 0),
            InvalidTitle
        );
        CHECK_THROWS_AS(
            InfiniteGame(4000001, "  ", pr, 100, AbstractGame::Average, 3, InfiniteGame::Average, true, 5, 0),
            InvalidTitle
        );
        CHECK_THROWS_AS(
            InfiniteGame(4000001, "\t\v", pr, 100, AbstractGame::Average, 3, InfiniteGame::Average, true, 5, 0),
            InvalidTitle
        );

        CHECK_THROWS_AS(
            InfiniteGame(4000001, "G", pr, 0, AbstractGame::Average, 3, InfiniteGame::Average, true, Price(500)),
            InvalidFilesSize
        );
        CHECK_THROWS_AS(
            InfiniteGame(4000001, "G", pr, 0, AbstractGame::Average, 3, InfiniteGame::Average, true, 5, 0),
            InvalidFilesSize
        );

        CHECK_THROWS_AS(
            InfiniteGame(4000001, "G", pr, 100, AbstractGame::Average, 0, InfiniteGame::Average, true, Price(500)),
            InvalidTestersAmount
        );
        CHECK_THROWS_AS(
            InfiniteGame(4000001, "G", pr, 100, AbstractGame::Average, 0, InfiniteGame::Average, true, 5, 0),
            InvalidTestersAmount
        );

        CHECK_THROWS_AS(
            InfiniteGame(4000001, "G", pr, 100, AbstractGame::Average, 3, InfiniteGame::Average, true, Price(-1)), InvalidPrice
        );
        CHECK_THROWS_AS(
            InfiniteGame(4000001, "G", pr, 100, AbstractGame::Average, 3, InfiniteGame::Average, true, -10), InvalidPrice
        );
        CHECK_THROWS_AS(
            InfiniteGame(4000001, "G", pr, 100, AbstractGame::Average, 3, InfiniteGame::Average, true, 5, -1), InvalidPrice
        );
        CHECK_THROWS_AS(
            InfiniteGame(4000001, "G", pr, 100, AbstractGame::Average, 3, InfiniteGame::Average, true, -1, 0), InvalidPrice
        );
        CHECK_THROWS_AS(
            InfiniteGame(4000001, "G", pr, 100, AbstractGame::Average, 3, InfiniteGame::Average, true, -2, 150), InvalidPrice
        );
    }
    SECTION("Title setter - typical")
    {
        game.setTitle("ABC");
        CHECK(game.getId() == 4000001);
        CHECK(game.getTitle() == "ABC");
        CHECK(&game.getProducer() == &pr);
        CHECK(game.getFilesSize() == 100);
        CHECK(game.getComplexity() == 1);
        CHECK(game.getDepth() == 0);
        CHECK(game.getCodeAvailable());
        CHECK(game.getMarketPrice() == Price(5, 0));
        CHECK(game.getMinTestersAmount() == 3);

        game.setTitle("Specje \tu Sa");
        CHECK(game.getId() == 4000001);
        CHECK(game.getTitle() == "Specje \tu Sa");
        CHECK(&game.getProducer() == &pr);
        CHECK(game.getFilesSize() == 100);
        CHECK(game.getComplexity() == 1);
        CHECK(game.getDepth() == 0);
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
        CHECK(game.getId() == 4000001);
        CHECK(game.getTitle() == "G");
        CHECK(&game.getProducer() == &pr);
        CHECK(game.getFilesSize() == 234);
        CHECK(game.getComplexity() == 1);
        CHECK(game.getDepth() == 0);
        CHECK(game.getCodeAvailable());
        CHECK(game.getMarketPrice() == Price(5, 0));
        CHECK(game.getMinTestersAmount() == 3);

        game.setFilesSize(734);
        CHECK(game.getId() == 4000001);
        CHECK(game.getTitle() == "G");
        CHECK(&game.getProducer() == &pr);
        CHECK(game.getFilesSize() == 734);
        CHECK(game.getComplexity() == 1);
        CHECK(game.getDepth() == 0);
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
        CHECK(game.getId() == 4000001);
        CHECK(game.getTitle() == "G");
        CHECK(&game.getProducer() == &pr);
        CHECK(game.getFilesSize() == 100);
        CHECK(game.getComplexity() == 1);
        CHECK(game.getDepth() == 0);
        CHECK(game.getCodeAvailable());
        CHECK(game.getMarketPrice() == Price(5, 0));
        CHECK(game.getMinTestersAmount() == 3);

        game.setCodeAvailable(false);
        CHECK(game.getId() == 4000001);
        CHECK(game.getTitle() == "G");
        CHECK(&game.getProducer() == &pr);
        CHECK(game.getFilesSize() == 100);
        CHECK(game.getComplexity() == 1);
        CHECK(game.getDepth() == 0);
        CHECK_FALSE(game.getCodeAvailable());
        CHECK(game.getMarketPrice() == Price(5, 0));
        CHECK(game.getMinTestersAmount() == 3);
    }
    SECTION("Complexity setter")
    {
        game.setComplexity(AbstractGame::Simple);
        CHECK(game.getId() == 4000001);
        CHECK(game.getTitle() == "G");
        CHECK(&game.getProducer() == &pr);
        CHECK(game.getFilesSize() == 100);
        CHECK(game.getComplexity() == 0);
        CHECK(game.getDepth() == 0);
        CHECK(game.getCodeAvailable());
        CHECK(game.getMarketPrice() == Price(5, 0));
        CHECK(game.getMinTestersAmount() == 3);

        game.setComplexity(AbstractGame::Complex);
        CHECK(game.getId() == 4000001);
        CHECK(game.getTitle() == "G");
        CHECK(&game.getProducer() == &pr);
        CHECK(game.getFilesSize() == 100);
        CHECK(game.getComplexity() == 2);
        CHECK(game.getDepth() == 0);
        CHECK(game.getCodeAvailable());
        CHECK(game.getMarketPrice() == Price(5, 0));
        CHECK(game.getMinTestersAmount() == 3);
    }
    SECTION("Depth setter")
    {
        game.setDepth(InfiniteGame::Deep);
        CHECK(game.getId() == 4000001);
        CHECK(game.getTitle() == "G");
        CHECK(&game.getProducer() == &pr);
        CHECK(game.getFilesSize() == 100);
        CHECK(game.getComplexity() == 1);
        CHECK(game.getDepth() == 1);
        CHECK(game.getCodeAvailable());
        CHECK(game.getMarketPrice() == Price(5, 0));
        CHECK(game.getMinTestersAmount() == 3);

        game.setDepth(InfiniteGame::Shallow);
        CHECK(game.getId() == 4000001);
        CHECK(game.getTitle() == "G");
        CHECK(&game.getProducer() == &pr);
        CHECK(game.getFilesSize() == 100);
        CHECK(game.getComplexity() == 1);
        CHECK(game.getDepth() == -1);
        CHECK(game.getCodeAvailable());
        CHECK(game.getMarketPrice() == Price(5, 0));
        CHECK(game.getMinTestersAmount() == 3);
    }
    SECTION("MinTestersAmount setter - typical")
    {
        game.setMinTestersAmount(1);
        CHECK(game.getId() == 4000001);
        CHECK(game.getTitle() == "G");
        CHECK(&game.getProducer() == &pr);
        CHECK(game.getFilesSize() == 100);
        CHECK(game.getComplexity() == 1);
        CHECK(game.getDepth() == 0);
        CHECK(game.getCodeAvailable());
        CHECK(game.getMarketPrice() == Price(5, 0));
        CHECK(game.getMinTestersAmount() == 1);

        game.setMinTestersAmount(734);
        CHECK(game.getId() == 4000001);
        CHECK(game.getTitle() == "G");
        CHECK(&game.getProducer() == &pr);
        CHECK(game.getFilesSize() == 100);
        CHECK(game.getComplexity() == 1);
        CHECK(game.getDepth() == 0);
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
        CHECK(game.getId() == 4000001);
        CHECK(game.getTitle() == "G");
        CHECK(&game.getProducer() == &pr);
        CHECK(game.getFilesSize() == 100);
        CHECK(game.getComplexity() == 1);
        CHECK(game.getDepth() == 0);
        CHECK(game.getCodeAvailable());
        CHECK(game.getMarketPrice() == Price(20, 12));
        CHECK(game.getMinTestersAmount() == 3);

        game.setMarketPrice(734);
        CHECK(game.getId() == 4000001);
        CHECK(game.getTitle() == "G");
        CHECK(&game.getProducer() == &pr);
        CHECK(game.getFilesSize() == 100);
        CHECK(game.getComplexity() == 1);
        CHECK(game.getDepth() == 0);
        CHECK(game.getCodeAvailable());
        CHECK(game.getMarketPrice() == Price(7, 34));
        CHECK(game.getMinTestersAmount() == 3);
    }
    SECTION("Market price setter 2 - typical")
    {
        game.setMarketPrice(234, 0);
        CHECK(game.getId() == 4000001);
        CHECK(game.getTitle() == "G");
        CHECK(&game.getProducer() == &pr);
        CHECK(game.getFilesSize() == 100);
        CHECK(game.getComplexity() == 1);
        CHECK(game.getDepth() == 0);
        CHECK(game.getCodeAvailable());
        CHECK(game.getMarketPrice() == Price(234, 0));
        CHECK(game.getMinTestersAmount() == 3);

        game.setMarketPrice(0, 120);
        CHECK(game.getId() == 4000001);
        CHECK(game.getTitle() == "G");
        CHECK(&game.getProducer() == &pr);
        CHECK(game.getFilesSize() == 100);
        CHECK(game.getComplexity() == 1);
        CHECK(game.getDepth() == 0);
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
        game.setComplexity(AbstractGame::Simple);
        game.setDepth(InfiniteGame::Average);
        game.setCodeAvailable(false);
        CHECK(game.getTestingTime() == 20);
        game.setFilesSize(200000);
        CHECK(game.getTestingTime() == 40);
        game.setCodeAvailable(true);
        CHECK(game.getTestingTime() == 32);
        game.setComplexity(AbstractGame::Complex);
        CHECK(game.getTestingTime() == 45);
        game.setDepth(InfiniteGame::Shallow);
        CHECK(game.getTestingTime() == 32);
        game.setDepth(InfiniteGame::Expansive);
        CHECK(game.getTestingTime() == 72);
        game.setMinTestersAmount(15);
        CHECK(game.getTestingTime() == 87);
    }
    SECTION("Price of testing")
    {
        game.setFilesSize(100000);
        game.setComplexity(AbstractGame::Simple);
        game.setDepth(InfiniteGame::Average);
        game.setCodeAvailable(false);
        CHECK(game.getTestingPrice() == Price(800, 0));
        game.setFilesSize(200000);
        CHECK(game.getTestingPrice() == Price(1600, 0));
        game.setCodeAvailable(true);
        CHECK(game.getTestingPrice() == Price(1280, 0));
        game.setComplexity(AbstractGame::Complex);
        CHECK(game.getTestingPrice() == Price(1800, 0));
        game.setDepth(InfiniteGame::Shallow);
        CHECK(game.getTestingPrice() == Price(1280, 0));
        game.setDepth(InfiniteGame::Expansive);
        CHECK(game.getTestingPrice() == Price(2880, 0));
        game.setMinTestersAmount(15);
        CHECK(game.getTestingPrice() == Price(3480, 0));
        game.setMarketPrice(0);
        CHECK(game.getTestingPrice() == Price(2784, 0));
        game.setMarketPrice(Price(110, 0));
        CHECK(game.getTestingPrice() == Price(3654, 0));
        game.setMarketPrice(Price(200, 0));
        CHECK(game.getTestingPrice() == Price(5220, 0));
    }
    SECTION("<< operator")
    {
        std::stringstream stream1, stream2;
        stream1 << game;
        stream2 << "InfiniteGame 1";
        CHECK(stream1.str() == stream2.str());

        InfiniteGame game1(4009000, "G", pr, 100, AbstractGame::Average, 3, InfiniteGame::Expansive, true, Price(500));
        stream1.str("");
        stream1.clear();
        stream2.str("");
        stream2.clear();

        Game *infgameptr = &game1;
        stream1 << *infgameptr;
        stream2 << "InfiniteGame 9000";
        CHECK(stream1.str() == stream2.str());
    }
    SECTION("Equality operators")
    {
        InfiniteGame &game2 = game;
        CHECK(game == game2);
        CHECK_FALSE(game != game2);
        game.setTitle("ABCD");
        CHECK(game2 == game);
        CHECK_FALSE(game != game2);

        InfiniteGame game1(4009000, "G", pr, 100, AbstractGame::Average, 3, InfiniteGame::Expansive, true, Price(500));
        CHECK_FALSE(game == game1);
        CHECK(game != game1);
        CHECK_FALSE(game1 == game2);
        CHECK(game1 != game2);
    }
}