
//
// Created by Kevin Schmidt on 12/15/21.
//

#include "matrices/matrix.hpp"
#include <gtest/gtest.h>

TEST(matrices, equalities)
{
    EXPECT_EQ(
        (Matrix<2,2>({{1,2},{3,4}})),
        (Matrix<2,2>({{1,2},{3,4}}))
    );

    EXPECT_NE(
        (Matrix<2,2>({{1,2},{3,4}})),
        (Matrix<2,2>({{4,3},{2,1}}))
    );
}

TEST(matrices, multiplications)
{
    EXPECT_EQ(
            (Matrix<2,2>({{1,2},{3,4}})*Matrix<2,2>({{1,2},{3,4}})),
            (Matrix<2,2>({{7,10},{15,22}}))
    );

    EXPECT_EQ(
            (Matrix<2,2,int>({{2,5},{3,4}})*Matrix<2,2,int>({{2,5},{3,4}})),
            (Matrix<2,2,int>({{19,30},{18,31}}))
    );

}

TEST(matrices, misc)
{
    Matrix<2,2> m1 ({{1, 2}, {3, 4}});
    Matrix<2,2> m2 ({{5, 6}, {7, 8}});
    Matrix<2,2> m3 = m1*m2;
    EXPECT_EQ(m3, (Matrix<2,2>({{19,22},{43,50}})));

    Matrix<3,1>pt({{1},{0},{1}});

    float x =
            error(
                    (rotate(90))
                    *
                    (Matrix<3,1>({{1},{0},{1}}))
                    ,
                    (Matrix<3,1>({{0},{1},{1}}))
            );

    EXPECT_LT(x, 0.0001);

    Matrix<3,1>p({{3},{4},{1}});
    p = rotate(270) * p;
    p = scale(2, 1) * p;
    p = translate(100,50) * p;
    p.normalize();

    EXPECT_LT(error(p, Matrix<3,1>{{108},{47},{1}}), 0.0001);

    auto transform = translate(100,50) * scale(2, 1) * rotate(270);
    EXPECT_LT(error( transform * Matrix<3,1>{{3},{4},{1}}, p), .0001);
}
