#include "catch.hpp"
#include "../games/price.h"
#include "../exceptions.h"
#include <sstream>


TEST_CASE("Price constructors", "[Price]")
{
    SECTION("Default constructor")
    {
        Price price = Price();
        CHECK(price.getZl() == 0);
    }
    SECTION("Constructor with 2 arguments - typical")
    {
        Price price(2, 55);
        CHECK(price.getZl() == 2);
        CHECK(price.getGr() == 55);
    }
    SECTION("Constructor with 2 arguments - 0 zł")
    {
        Price price(0, 55);
        CHECK(price.getZl() == 0);
        CHECK(price.getGr() == 55);
    }
    SECTION("Constructor with 2 arguments - 0 gr")
    {
        Price price(2, 0);
        CHECK(price.getZl() == 2);
        CHECK(price.getGr() == 0);
    }
    SECTION("Constructor with 2 arguments - 0 zł and 0 gr")
    {
        Price price(0, 0);
        CHECK(price.getZl() == 0);
        CHECK(price.getGr() == 0);
    }
    SECTION("Constructor with 2 arguments - more than 99 gr")
    {
        Price price(0, 110);
        CHECK(price.getZl() == 1);
        CHECK(price.getGr() == 10);
        price = Price(56, 100);
        CHECK(price.getZl() == 57);
        CHECK(price.getGr() == 0);
    }
    SECTION("Constructor with 2 arguments - negative zł")
    {
        CHECK_THROWS_AS(Price(-1, 134), InvalidPrice);
        CHECK_THROWS_AS(Price(-45, 0), InvalidPrice);
        CHECK_THROWS_AS(Price(-2, 90), InvalidPrice);
        CHECK_THROWS_AS(Price(-50, -3), InvalidPrice);
    }
    SECTION("Constructor with 2 arguments - negative gr")
    {
        CHECK_THROWS_AS(Price(0, -1), InvalidPrice);
        CHECK_THROWS_AS(Price(4, -50), InvalidPrice);
        CHECK_THROWS_AS(Price(8, -110), InvalidPrice);
        CHECK_THROWS_AS(Price(-2, -20), InvalidPrice);
    }
    SECTION("Constructor with 1 argument - typical")
    {
        Price price(10);
        CHECK(price.getZl() == 0);
        CHECK(price.getGr() == 10);
    }
    SECTION("Constructor with 1 argument - more than 100 gr")
    {
        Price price(160);
        CHECK(price.getZl() == 1);
        CHECK(price.getGr() == 60);
    }
    SECTION("Constructor with 1 argument - zero")
    {
        Price price(0);
        CHECK(price.getZl() == 0);
        CHECK(price.getGr() == 0);
    }
    SECTION("Constructor with 1 argument - negative")
    {
        CHECK_THROWS_AS(Price(-1), InvalidPrice);
        CHECK_THROWS_AS(Price(-50), InvalidPrice);
        CHECK_THROWS_AS(Price(-150), InvalidPrice);
    }
}


TEST_CASE("Price setters", "[Price]")
{
    Price price(1, 50);
    CHECK(price.getZl() == 1);
    CHECK(price.getGr() == 50);
    SECTION("Zl setter - typical")
    {
        price.setZl(50);
        CHECK(price.getZl() == 50);
        CHECK(price.getGr() == 50);
        price.setZl(150);
        CHECK(price.getZl() == 150);
        CHECK(price.getGr() == 50);
        price.setZl(0);
        CHECK(price.getZl() == 0);
        CHECK(price.getGr() == 50);
    }
    SECTION("Zl setter - exceptions")
    {
        CHECK_THROWS_AS(price.setZl(-1), InvalidPrice);
        CHECK_THROWS_AS(price.setZl(-50), InvalidPrice);
    }
    SECTION("Gr setter - typical")
    {
        price.setGr(50);
        CHECK(price.getZl() == 1);
        CHECK(price.getGr() == 50);
        price.setGr(72);
        CHECK(price.getZl() == 1);
        CHECK(price.getGr() == 72);
        price.setGr(0);
        CHECK(price.getZl() == 1);
        CHECK(price.getGr() == 0);
    }
    SECTION("Gr setter - exceptions")
    {
        CHECK_THROWS_AS(price.setGr(-1), InvalidPrice);
        CHECK_THROWS_AS(price.setGr(-50), InvalidPrice);
        CHECK_THROWS_AS(price.setGr(100), InvalidPrice);
        CHECK_THROWS_AS(price.setGr(123), InvalidPrice);
    }
}


TEST_CASE("Price operators", "[Price]")
{
    std::stringstream stream;
    SECTION("<< operator - typical cases")
    {
        Price price(1, 50);
        stream << price;
        CHECK(stream.str() == "1 zł 50 gr");
        stream.str("");
        stream.clear();

        price = Price(20, 34);
        stream << price;
        CHECK(stream.str() == "20 zł 34 gr");
    }
    SECTION("<< operator - 0 zł case")
    {
        Price price(0, 50);
        stream << price;
        CHECK(stream.str() == "50 gr");
    }
    SECTION("<< operator - 0 gr case")
    {
        Price price(2, 0);
        stream << price;
        CHECK(stream.str() == "2 zł");
    }
    SECTION("<< operator - zero case")
    {
        Price price = Price();
        stream << price;
        CHECK(stream.str() == "0 zł");
    }
    SECTION("!= operator")
    {
        Price price1(1, 50);
        Price price2(20, 34);
        CHECK(price1 != price2);
        price1 = Price(1, 50);
        price2 = Price(160);
        CHECK(price1 != price2);
        price1 = Price(0);
        price2 = Price(0, 1);
        CHECK(price1 != price2);
        price1 = Price(1, 50);
        price2 = Price(1, 50);
        CHECK_FALSE(price1 != price2);
        price1 = Price(1, 60);
        price2 = Price(160);
        CHECK_FALSE(price1 != price2);
        price1 = Price(0);
        price2 = Price();
        CHECK_FALSE(price1 != price2);
    }
    SECTION("== operator")
    {
        Price price1(1, 50);
        Price price2(1, 50);
        CHECK(price1 == price2);
        price1 = Price(1, 60);
        price2 = Price(160);
        CHECK(price1 == price2);
        price1 = Price(0);
        price2 = Price();
        CHECK(price1 == price2);
        price1 = Price(1, 50);
        price2 = Price(20, 34);
        CHECK_FALSE(price1 == price2);
        price1 = Price(1, 50);
        price2 = Price(160);
        CHECK_FALSE(price1 == price2);
        price1 = Price(0);
        price2 = Price(0, 1);
        CHECK_FALSE(price1 == price2);
    }
    SECTION("Comparison operators")
    {
        Price price1(23, 50);
        Price price2(2, 50);
        CHECK(price1 > price2);
        CHECK(price1 >= price2);
        CHECK_FALSE(price1 < price2);
        CHECK_FALSE(price1 <= price2);

        price2.setZl(23);
        CHECK_FALSE(price1 > price2);
        CHECK(price1 >= price2);
        CHECK_FALSE(price1 < price2);
        CHECK(price1 <= price2);

        price2.setGr(60);
        CHECK_FALSE(price1 > price2);
        CHECK_FALSE(price1 >= price2);
        CHECK(price1 < price2);
        CHECK(price1 <= price2);
    }
    SECTION("Addition operators")
    {
        Price price1(23, 50);
        Price price2(2, 50);
        Price price3 = price1 + price2;
        CHECK(price3.getZl() == 26);
        CHECK(price3.getGr() == 0);

        price3 += price2;
        CHECK(price3.getZl() == 28);
        CHECK(price3.getGr() == 50);

        price3 += Price();
        CHECK(price3.getZl() == 28);
        CHECK(price3.getGr() == 50);
    }
    SECTION("Subtraction operators")
    {
        Price price1(23, 50);
        Price price2(2, 50);
        Price price3 = price1 - price2;
        CHECK(price3.getZl() == 21);
        CHECK(price3.getGr() == 0);

        price3 -= price2;
        CHECK(price3.getZl() == 18);
        CHECK(price3.getGr() == 50);

        price3 -= Price();
        CHECK(price3.getZl() == 18);
        CHECK(price3.getGr() == 50);

        CHECK_THROWS_AS(price3 - price1, InvalidPrice);
        CHECK_THROWS_AS(price3 -= price1, InvalidPrice);

        Price price4 = price3 - price3;
        CHECK(price4.getZl() == 0);
        CHECK(price4.getGr() == 0);

        price3 -= price3;
        CHECK(price3.getZl() == 0);
        CHECK(price3.getGr() == 0);
    }
    SECTION("Multiplication operators")
    {
        Price price1(2, 30);
        Price price2 = price1 * 3;
        CHECK(price2.getZl() == 6);
        CHECK(price2.getGr() == 90);
        price2 *= 1.5;
        CHECK(price2.getZl() == 10);
        CHECK(price2.getGr() == 35);

        CHECK_THROWS_AS(price2 * -1, InvalidPrice);
        CHECK_THROWS_AS(-1 * price2, InvalidPrice);
        CHECK_THROWS_AS(price2 *= -1, InvalidPrice);

        price2 *= 0;
        CHECK(price2.getZl() == 0);
        CHECK(price2.getGr() == 0);

        price2 = 3 * price1;
        CHECK(price2.getZl() == 6);
        CHECK(price2.getGr() == 90);

        price2 = 0 * price1;
        CHECK(price2.getZl() == 0);
        CHECK(price2.getGr() == 0);
    }
    SECTION("Conversion operators")
    {
        Price price(2, 30);
        CHECK(int(price) == 3);
        CHECK(double(price) == Approx(2.3));

        price = Price(6, 0);
        CHECK(int(price) == 6);
        CHECK(double(price) == Approx(6));
    }
}
