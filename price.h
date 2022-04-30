#ifndef PRICE_H
#define PRICE_H
#include <string>
#include <ostream>


/*
Price class representing a price in Polish currency (PLN).
*/
class Price
{
private:
    int zl;
    int gr;
    // Returns true if and only if a price with these zl and gr values would be valid.
    static bool checkPrice(int zl, int gr) noexcept;
    // Returns the value of the price in gr.
    int getValueInGr() const noexcept;
public:
    // This constructor will create a price of 0 zł 0 gr.
    Price() noexcept;
    // This constructor will accept gr>=100 and convert excess gr to zl, unlike the gr setter.
    Price(int zl, int gr);
    Price(int priceInGr);
    int getZl() const noexcept;
    // Throws InvalidPrice if newZl<0.
    void setZl(int newZl);
    int getGr() const noexcept;
    // Throws InvalidPrice if newGr<0 or newGr>=100
    void setGr(int newGr);
    friend std::ostream& operator<<(std::ostream &stream, const Price &price) noexcept;
    // == is the base operator
    bool operator==(const Price& price) const noexcept;
    bool operator!=(const Price& price) const noexcept;
    // < is a base operator, other comparison operators use it and ==.
    bool operator<(const Price& price) const noexcept;
    bool operator<=(const Price& price) const noexcept;
    bool operator>(const Price& price) const noexcept;
    bool operator>=(const Price& price) const noexcept;
    // +, -, *(Price, int) are base operators.
    Price operator+(const Price& price) const noexcept;
    Price& operator+=(const Price& price) noexcept;
    // Subtraction throws InvalidPrice if the result is negative.
    Price operator-(const Price& price) const;
    Price& operator-=(const Price& price);
    // Multiplication throws InvalidPrice if the factor is negative.
    Price operator*(double factor) const;
    friend Price operator*(double factor, const Price &price);
    Price& operator*=(double factor);
    explicit operator int() const;
    explicit operator double() const;
};


#endif
