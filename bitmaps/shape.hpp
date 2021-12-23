//
// Created by Kevin Schmidt on 12/21/21.
//

#ifndef CLASSES_SHAPE_HPP
#define CLASSES_SHAPE_HPP
#include "bitmapz.hpp"

Matrix<4,4> return_1_(float t);

class Shape
{
    Matrix<4,4> (*transform_)(float t);
public:

    Shape(std::shared_ptr<TriangleList> triangles, Matrix<4,4> (*transform)(float t) = &return_1_)
        : triangles_(triangles)
        , transform_(transform){};

    std::shared_ptr<TriangleList> triangles_;
    std::vector<Shape> sub_shapes_;

    virtual Matrix<4,4> get_transform(float t) const { return transform_(t); }

    void draw(BitmapZ &b, Matrix<4,4> const &transform, float t) const;
    void make_frames(int width, int height, Matrix<4,4> pov, float t1, float t2, float fps, char const * filename, float x1, float x2, float y1, float y2);

};


#endif //CLASSES_SHAPE_HPP
