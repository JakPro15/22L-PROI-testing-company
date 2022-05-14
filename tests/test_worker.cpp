#include "catch.hpp"
#include "../worker.h"
#include "../exceptions.h"
#include <sstream>

TEST_CASE("Worker methods", "[Worker]")
{
    Worker piekarz(8000001, "Paweł", "Piekarski");

    SECTION("Constructor and getters")
    {
        Worker butcher(8000002, "Jan", "Rzeźnicki");

        CHECK(butcher.getId() == 8000002);
        CHECK(butcher.getName() == "Jan");
        CHECK(butcher.getSurname() == "Rzeźnicki");
    }

    SECTION("Constructor-exceptions")
    {
        CHECK_THROWS_AS(Worker(1, "Jan", "Kowalski"), InvalidId);
        CHECK_THROWS_AS(Worker(8000002, "\n", "Kowalski"), EmptyNameException);
        CHECK_THROWS_AS(Worker(8000002, "Jan", "   "), EmptyNameException);
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

    SECTION("Comparison operators")
    {
        Worker evil_clone(8000001, "Graweł", "Piekarski");
        Worker random(8000002, "Losowy", "Typ");

        CHECK((piekarz == evil_clone) == true);
        CHECK((piekarz != evil_clone) == false);

        CHECK((piekarz == random) == false);
        CHECK((piekarz != random) == true);
    }

    SECTION("Stream operator")
    {
        std::stringstream stream1, stream2;

        stream1 << piekarz;
        stream2 << "Worker 1";

        CHECK(stream1.str() == stream2.str());

        stream1.str("");
        stream1.clear();
        stream2.str("");
        stream2.clear();

        Worker random(8000002, "Losowy", "Typ");

        stream1 << random;
        stream2 << "Worker 2";

        CHECK(stream1.str() == stream2.str());
    }
}