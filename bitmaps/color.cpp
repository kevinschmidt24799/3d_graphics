//
// Created by Kevin Schmidt on 12/16/21.
//

#include "color.hpp"
#include "matrices/matrix.hpp"
static Matrix<3,3> toYUV {{0.2126, 0.7152, 0.0722},
                          {-0.09991 , -0.33609, 0.436},
                          {0.615, -0.55861, -0.05639}};

static Matrix<3,3> toRGB {{1, 0, 1.28033},
                          {1,-0.21482, -0.38059},
                          {1, 2.12798, 0}};

Color Color::set_brightness(float brightness)
{
    brightness = (1+4*brightness)/5;
    Matrix<3,1> c = {{static_cast<float>(r_)},
                     {static_cast<float>(g_)},
                     {static_cast<float>(b_)}};
    c = toYUV * c;
    c.data_[2][0] *= brightness;
    c.data_[1][0] *= brightness;
    c.data_[0][0] *= brightness;
    c = toRGB * c;

    return Color(static_cast<unsigned char>(c.data_[0][0]),
                 static_cast<unsigned char>(c.data_[1][0]),
                 static_cast<unsigned char>(c.data_[2][0]));
}