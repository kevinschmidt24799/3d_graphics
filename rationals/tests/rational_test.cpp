//
// Created by Kevin Schmidt on 12/15/21.
//

#include "gtest/gtest.h"
#include "rationals/Rational.hpp"

TEST(rationals, simplify)
{
    EXPECT_EQ(Rational(27,36),Rational(3,4));
    EXPECT_EQ(Rational(-27,36),Rational(-3,4));
    EXPECT_EQ(Rational(27,-36),Rational(-3,4));
    EXPECT_EQ(Rational(-27,-36),Rational(3,4));
}

TEST(rationals, multiplicative)
{
    EXPECT_EQ(Rational(5,4)*Rational(16,20),Rational(1));
    EXPECT_EQ(Rational(5,4)*Rational(16,-20),Rational(-1));
    EXPECT_EQ(Rational(0,7)*Rational(5,5),Rational(0));
    EXPECT_EQ(Rational(101)/Rational(7,2),Rational(202,7));
    EXPECT_EQ(Rational(101)/Rational(7,-2),Rational(202,-7));
    EXPECT_EQ(Rational(0)/Rational(3,4),Rational(0));
    EXPECT_EQ(Rational(0,7)*Rational(5,5),Rational(0));
}

TEST(rationals, additive)
{
    EXPECT_EQ(Rational(2,3)+Rational(1,4),Rational(11,12));
    EXPECT_EQ(Rational(11,12)-Rational(2,3),Rational(2,8));
    EXPECT_EQ(Rational(7,9)+Rational(4,18),Rational(1));
}


