//
// Created by Kevin Schmidt on 12/15/21.
//

#include "matrix.hpp"
#include "math.h"

Matrix<3,3,float> rotate(float degrees)
{
    Matrix<3,3,float>out;
    float radians = degrees * M_PI/180;

    out.data_[0][0] = cos(radians);
    out.data_[0][1] = -sin(radians);
    out.data_[1][0] = sin(radians);
    out.data_[1][1] = cos(radians);

    return out;
}

Matrix<3,3> translate(float tx, float ty)
{
    Matrix<3,3> out;
    out.data_[0][2] = tx;
    out.data_[1][2] = ty;
    return out;
}

Matrix<3,3> scale(float sx, float sy)
{
    Matrix<3,3> out;
    out.data_[0][0] = sx;
    out.data_[1][1] = sy;
    return out;
}

Matrix<3,3> scale(float s)
{
    return scale(s,s);
}


Matrix<4,4> rotate(float degrees,float l,float m,float n)
{
    float magnitude = sqrt(l*l+m*m+n*n);
    l/= magnitude;
    m/= magnitude;
    n/= magnitude;

    Matrix<4,4>out;
    float radians = degrees * M_PI/180;
    float cos = cosf(radians);
    float sin = sinf(radians);

    out.data_[0][0] = l*l*(1- cos) + cos;
    out.data_[0][1] = m*l*(1- cos) - n*sin;
    out.data_[0][2] = n*l*(1- cos) + m*sin;

    out.data_[1][0] = l*m*(1- cos) + n*sin;
    out.data_[1][1] = m*m*(1- cos) + cos;
    out.data_[1][2] = n*m*(1- cos) - l*sin;

    out.data_[2][0] = l*n*(1- cos) - m*sin;
    out.data_[2][1] = m*n*(1- cos) + l*sin;
    out.data_[2][2] = n*n*(1- cos) + cos;

    return out;
}

Matrix<4,4> translate(float tx, float ty, float tz)
{
    Matrix<4,4> out;
    out.data_[0][3] = tx;
    out.data_[1][3] = ty;
    out.data_[2][3] = tz;
    return out;
}

Matrix<4,4> scale(float sx, float sy, float sz)
{
    Matrix<4,4> out;
    out.data_[0][0] = sx;
    out.data_[1][1] = sy;
    out.data_[2][2] = sz;
    return out;
}

Matrix<4,4> scale3d(float s)
{
    return scale(s,s,s);
}

Matrix<4,4> perspective(float altitude)
{
    Matrix<4,4> out;
//    out.data_[3][3] = 0;
//    out.data_[3][2] = -3.0/2;
//    out.data_[2][3] = -1;
//    out.data_[2][2] = -3.0/2;
    out.data_[3][3] = 0.0;
    out.data_[3][2] = -1.0;
    out.data_[2][2] = -1.0;
    out.data_[2][3] = -1.0;

    return out * translate(0,0,altitude);
}