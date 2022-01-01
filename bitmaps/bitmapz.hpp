//
// Created by Kevin Schmidt on 12/18/21.
//

#ifndef CLASSES_BITMAPZ_HPP
#define CLASSES_BITMAPZ_HPP

#include "bitmap.hpp"
#include <vector>

struct Triangle
{
    Matrix<4,1> p1_, p2_, p3_;
    Color c1_, c2_, c3_;
    Triangle(Matrix<4,1> p1, Matrix<4,1> p2, Matrix<4,1> p3, Color c1, Color c2, Color c3)
        :p1_(p1), p2_(p2), p3_(p3), c1_(c1), c2_(c2), c3_(c3){}
    Triangle(Matrix<4,1> p1, Matrix<4,1> p2, Matrix<4,1> p3, Color c)
        :p1_(p1), p2_(p2), p3_(p3), c1_(c), c2_(c), c3_(c){}

    Triangle transform(Matrix<4,4> const &m) const;
    float direction(Matrix<4,1> p);
};

typedef std::vector<Triangle> TriangleList;

class BitmapZ : public Bitmap
{
public:
    float * z_buffer_;

    BitmapZ(int w, int h);
    ~BitmapZ();

    void set_pixel(int x, int y, float z, Color const &c);
    void draw_triangle(Matrix<4,1> p1, Matrix<4,1> p2, Matrix<4,1> p3, Color c1 = white, Color c2 = white, Color c3 = white);
    void draw_triangle(Triangle t);

    void horizontal_line(int y, int x1, int x2, float z1, float z2, Color c1, Color c2);

    void fill_all(const Color &c);

};

std::shared_ptr<TriangleList> disc(float r, float height, int segments, Color c = Color(255,0,255), Color c2 = Color(200,200,200));




#endif //CLASSES_BITMAPZ_HPP
