#include "catch.hpp"
#include "../producer/producerdatabase.h"
#include "../producer/producer.h"
#include "../testingcompany/testingcompany.h"
#include "../simulation/simulation.h"
#include "../games/game.h"
#include "../exceptions.h"
#include <sstream>


TEST_CASE("Producer methods", "[Producer]")
{
    Simulation sim;
    TestingCompany tcom;
    OutputHandler out;
    Producer producer(out, 14000001, "Pr", Address("SN", 2, 5, "SNville", "12-345"), sim, tcom);
    SECTION("Constructor and getters - typical")
    {
        CHECK(producer.id == 14000001);
        CHECK(producer.getName() == "Pr");
        CHECK(producer.getAddress() == Address("SN", 2, 5, "SNville", "12-345"));
        CHECK(producer.simulation == sim);
        CHECK(producer.testingCompany == tcom);

        Simulation sim2;
        TestingCompany tcom2;
        Producer producer2(out, 14999999, "Prodd", Address("Zakopińska", 11, 11, "Zakopane", "33-333"), sim2, tcom2);
        CHECK(producer2.id == 14999999);
        CHECK(producer2.getName() == "Prodd");
        CHECK(producer2.getAddress() == Address("Zakopińska", 11, 11, "Zakopane", "33-333"));
        CHECK(producer2.simulation == sim2);
        CHECK(producer2.testingCompany == tcom2);
    }
    SECTION("Constructor - exceptions")
    {
        CHECK_THROWS_AS(Producer(out, 14000000, "Pr", Address("SN", 2, 5, "SNville", "12-345"), sim, tcom), InvalidId);
        CHECK_THROWS_AS(Producer(out, 15000000, "Pr", Address("SN", 2, 5, "SNville", "12-345"), sim, tcom), InvalidId);

        CHECK_THROWS_AS(Producer(out, 14000001, "", Address("SN", 2, 5, "SNville", "12-345"), sim, tcom), EmptyNameException);
        CHECK_THROWS_AS(Producer(out, 14000001, "  ", Address("SN", 2, 5, "SNville", "12-345"), sim, tcom), EmptyNameException);
        CHECK_THROWS_AS(Producer(out, 14000001, "\t\v\n", Address("SN", 2, 5, "SNville", "12-345"), sim, tcom), EmptyNameException);
    }
    SECTION("Name setter - typical")
    {
        producer.setName("ABCD");
        CHECK(producer.id == 14000001);
        CHECK(producer.getName() == "ABCD");
        CHECK(producer.getAddress() == Address("SN", 2, 5, "SNville", "12-345"));
        CHECK(producer.simulation == sim);
        CHECK(producer.testingCompany == tcom);

        producer.setName("Prri Ducceer");
        CHECK(producer.id == 14000001);
        CHECK(producer.getName() == "Prri Ducceer");
        CHECK(producer.getAddress() == Address("SN", 2, 5, "SNville", "12-345"));
        CHECK(producer.simulation == sim);
        CHECK(producer.testingCompany == tcom);
    }
    SECTION("Name setter - exceptions")
    {
        CHECK_THROWS_AS(producer.setName(""), EmptyNameException);
        CHECK_THROWS_AS(producer.setName("  "), EmptyNameException);
        CHECK_THROWS_AS(producer.setName("\t\r\n\v"), EmptyNameException);
    }
    SECTION("Address setter")
    {
        producer.setAddress(Address("Ulica", 1, 2, "City", "34-343"));
        CHECK(producer.id == 14000001);
        CHECK(producer.getName() == "Pr");
        CHECK(producer.getAddress() == Address("Ulica", 1, 2, "City", "34-343"));
        CHECK(producer.simulation == sim);
        CHECK(producer.testingCompany == tcom);

        producer.setAddress(Address("Ul Ull", 12, 12, "Yeet", "00-000"));
        CHECK(producer.id == 14000001);
        CHECK(producer.getName() == "Pr");
        CHECK(producer.getAddress() == Address("Ul Ull", 12, 12, "Yeet", "00-000"));
        CHECK(producer.simulation == sim);
        CHECK(producer.testingCompany == tcom);
    }
    SECTION("Equality operators")
    {
        Producer &producerRef = producer;
        CHECK(producer == producerRef);
        CHECK_FALSE(producer != producerRef);

        Producer producer2(out, 14000002, "Pr", Address("SN", 2, 5, "SNville", "12-345"), sim, tcom);
        CHECK(producer != producer2);
        CHECK_FALSE(producer == producer2);
    }
    SECTION("<< operator")
    {
        std::stringstream stream1, stream2;
        stream1 << producer;
        stream2 << "Producer 1";
        CHECK(stream1.str() == stream2.str());

        Producer producer2(out, 14009000, "Prodd", Address("Zakopińska", 11, 11, "Zakopane", "33-333"), sim, tcom);
        stream1.str("");
        stream1.clear();
        stream2.str("");
        stream2.clear();

        stream1 << producer2;
        stream2 << "Producer 9000";
        CHECK(stream1.str() == stream2.str());
    }
}