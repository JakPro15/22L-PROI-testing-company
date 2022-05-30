#ifndef TESTINGCOMPANY_H
#define TESTINGCOMPANY_H


class AbstractGame;


class TestingCompany
{
private:
    // Current amount of effort the company can use.
    unsigned int effort;
public:
    TestingCompany(...) {}

    // Copying of TestingCompany is forbidden (IDs wouldn't be unique).
    TestingCompany(const TestingCompany&)=delete;
    TestingCompany& operator=(const TestingCompany&)=delete;

    ~TestingCompany() {}
    int getRequestId() { return 11000001; }

    // Adding increases effort held by the company by specified amount.
    void addEffort(unsigned int effort) {this->effort += effort;}

    void testingFinished(const AbstractGame &game) {}
    void paymentDone(const AbstractGame &game) {}
    void sendTestingRequest(const AbstractGame &game) {}

    void advanceTime();

    bool operator==(const TestingCompany &company) const noexcept { return this == &company; }
    bool operator!=(const TestingCompany &company) const noexcept { return not (*this == company); };

    friend std::ostream& operator<<(std::ostream &stream, const TestingCompany &company) noexcept { return stream; }
};


#endif
