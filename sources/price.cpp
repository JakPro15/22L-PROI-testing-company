#include "../price.h"
#include "../exceptions/invalidprice.h"
#include <cmath>


bool Price::checkPrice(int zl, int gr) noexcept
{
    if(gr >= 100 or zl < 0 or gr < 0)
        return false;
    else
        return true;
}


int Price::getValueInGr() const noexcept
{
    return zl * 100 + gr;
}


Price::Price() noexcept : zl(0), gr(0)
{}


Price::Price(int zl, int gr) : zl(zl), gr(gr)
{
    if(this->zl >= 0 and this->gr >= 100)
    {
        int additional_zl = this->gr / 100;
        this->zl += additional_zl;
        this->gr -= additional_zl * 100;
    }
    if(not Price::checkPrice(this->zl, this->gr))
        throw InvalidPrice(this->zl, this->gr);
}


Price::Price(int priceInGr)
{
    if(priceInGr < 0)
        throw InvalidPrice(priceInGr);
    else
    {
        zl = priceInGr / 100;
        gr = priceInGr % 100;
    }
}


int Price::getZl() const noexcept
{
    return zl;
}


void Price::setZl(int newZl)
{
    if(not Price::checkPrice(newZl, gr))
        throw InvalidPrice(newZl, gr);
    else
        zl = newZl;
}


int Price::getGr() const noexcept
{
    return gr;
}


void Price::setGr(int newGr)
{
    if(not Price::checkPrice(zl, newGr))
        throw InvalidPrice(zl, newGr);
    else
        gr = newGr;
}


std::ostream& operator<<(std::ostream &stream, const Price &price) noexcept
{
    if(price.zl > 0 and price.gr > 0)
        stream << std::to_string(price.zl) << " zł " << std::to_string(price.gr) << " gr";
    else if(price.zl > 0)
        stream << std::to_string(price.zl) << " zł"; // skipping gr if it's equal to 0
    else if(price.gr > 0)
        stream << std::to_string(price.gr) << " gr"; // skipping zl if it's equal to 0
    else
        stream << "0 zł"; // 0 zł string for the price of zero
    return stream;
}


bool Price::operator==(const Price& price) const noexcept
{
    // Prices are equal if an only if both zl and gr are equal
    if(getZl() == price.getZl() and getGr() == price.getGr())
        return true;
    else
        return false;
}


bool Price::operator!=(const Price& price) const noexcept
{
    return not (*this == price);
}


bool Price::operator<(const Price& price) const noexcept
{
    return getValueInGr() < price.getValueInGr();
}


bool Price::operator<=(const Price& price) const noexcept
{
    return (*this < price) or (*this == price);
}


bool Price::operator>(const Price& price) const noexcept
{
    return not (*this <= price);
}


bool Price::operator>=(const Price& price) const noexcept
{
    return not (*this < price);
}


Price Price::operator+(const Price& price) const noexcept
{
    return Price(getValueInGr() + price.getValueInGr());
}


Price& Price::operator+=(const Price& price) noexcept
{
    Price result = *this + price;
    zl = result.zl;
    gr = result.gr;
    return *this;
}


Price Price::operator-(const Price& price) const
{
    return Price(getValueInGr() - price.getValueInGr());
}


Price& Price::operator-=(const Price& price)
{
    Price result = *this - price;
    zl = result.zl;
    gr = result.gr;
    return *this;
}


Price Price::operator*(double factor) const
{
    return Price(getValueInGr() * factor);
}


Price operator*(double factor, const Price &price)
{
    return price * factor;
}


Price& Price::operator*=(double factor)
{
    Price result = *this * factor;
    zl = result.zl;
    gr = result.gr;
    return *this;
}


Price::operator int() const
{
    return ceil(double(*this));
}


Price::operator double() const
{
    return double(zl + gr / 100.0);
}