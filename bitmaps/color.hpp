//
// Created by Kevin Schmidt on 12/16/21.
//

#ifndef CLASSES_COLOR_HPP
#define CLASSES_COLOR_HPP
#include "assert.h"


class Color
{
public:
    unsigned char r_;
    unsigned char g_;
    unsigned char b_;
    unsigned char a_;

    Color(int r, int g, int b, int a=255)
    {
        assert(r >= 0 && r <=255);
        assert(g >= 0 && g <=255);
        assert(b >= 0 && b <=255);
        assert(a >= 0 && a <=255);

        r_ = r;
        g_ = g;
        b_ = b;
        a_ = a;
    }

    void invert()
    {
        r_ = 255 - r_;
        g_ = 255 - g_;
        b_ = 255 - b_;
        a_ = 255 - a_;
    }

    Color set_brightness(float brightness);
};

inline Color white(255,255,255);

#endif //CLASSES_COLOR_HPP
