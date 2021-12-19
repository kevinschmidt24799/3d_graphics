//
// Created by Kevin Schmidt on 12/14/21.
//

#include <cmath>
#include <iostream>
#include "Rational.hpp"

Rational::Rational()
{
    num_ = 0;
    den_ = 1;
}
Rational::Rational(int n)
{
    num_ = n;
    den_ = 1;
}
Rational::Rational(int n, int d)
{
    num_ = n;
    den_ = d;
    simplify();
}

void Rational::simplify()
{

    if (num_ == 0)
    {
        den_ = 1;
        return;
    }

    if(den_ < 0)
    {
        den_ *= -1;
        num_ *= -1;
    }

    int a = abs(num_);
    int b = den_;

    while (a!=b)
    {
        if(a>b)
        {
            a%=b;
            if(a == 0)
            {
                a = b;
                break;
            }
        } else {
            b%=a;
            if(b == 0)
            {
                break;
            }
        }
    }
    num_ /= a;
    den_ /= a;
}

Rational Rational::operator+(Rational const &other)const
{
    Rational out(num_*other.den_ + other.num_*den_ , den_*other.den_);
    return out;
}

Rational Rational::operator-(Rational const &other)const
{
    Rational out(num_*other.den_ - other.num_*den_ , den_*other.den_);
    return out;
}

Rational Rational::operator*(Rational const &other)const
{
    Rational out(num_*other.num_ , den_*other.den_);
    return out;
}

Rational Rational::operator/(Rational const &other)const
{
    Rational out(num_*other.den_ , den_*other.num_);
    return out;
}

bool Rational::operator==(Rational const &other) const
{
    return (num_ == other.num_ && den_ == other.den_);
}

void Rational::print() const
{
    if(den_ == 0)
    {
        std::cout << "NaN";
    }
    std::cout << num_;
    if (den_ != 1)
    {
        std::cout << '/' << den_;
    }
}

std::ostream& operator<<(std::ostream& os, Rational const &other)
{
    if(other.den_ == 0)
    {
        os << "NaN";
    }
    os << other.num_;
    if (other.den_ != 1)
    {
        os << '/' << other.den_;
    }
    return os;
}



