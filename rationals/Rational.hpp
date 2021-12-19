//
// Created by Kevin Schmidt on 12/14/21.
//

#ifndef CLASSES_RATIONAL_HPP
#define CLASSES_RATIONAL_HPP


class Rational
{
public:
    int num_;
    int den_;

    Rational();
    Rational(int n);
    Rational(int n, int d);

    Rational operator+(Rational const &other) const;
    Rational operator-(Rational const &other) const;

    Rational operator*(Rational const &other) const;
    Rational operator/(Rational const &other) const;

    bool operator==(Rational const &other) const;

    void print() const;
    friend std::ostream& operator<<(std::ostream& os, Rational const &other);

private:
    void simplify();
};


#endif //CLASSES_RATIONAL_HPP
