//
// Created by Kevin Schmidt on 12/18/21.
//

#ifndef CLASSES_LINEARIZATION_HPP
#define CLASSES_LINEARIZATION_HPP


class Linearization
{
    int d1_, r1_, i_;

    int dr_;
    int dd_;
    int D_;
    int rdirection_;
    int rincrement_;

public:
    int d_, d2_;
    int r_, r2_;

    Linearization(int d1, int d2, int r1, int r2, int i = 1);
    void next();
};

bool test(int d1, int d2, int r1, int r2, int i=1);

class Linfloat
{
    float rincrement_;
    int i_;
public:
    int d_, d2_;
    float r_, r2_;

    Linfloat(int d1, int d2, float r1, float r2);
    void next();
};

#endif //CLASSES_LINEARIZATION_HPP
