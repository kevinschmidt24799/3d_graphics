//
// Created by Kevin Schmidt on 12/18/21.
//

#ifndef CLASSES_BITMAPZ_HPP
#define CLASSES_BITMAPZ_HPP

#include "bitmap.hpp"

class BitmapZ : public Bitmap
{
public:
    float * z_buffer_;

    BitmapZ(int w, int h);
    ~BitmapZ();

    void set_pixel(int x, int y, float z, Color const &c);
    void draw_triangle(Matrix<4,1> p1, Matrix<4,1> p2, Matrix<4,1> p3, Color c1 = white, Color c2 = white, Color c3 = white);
    void horizontal_line(int y, int x1, int x2, float z1, float z2, Color c1, Color c2);

};


#endif //CLASSES_BITMAPZ_HPP
