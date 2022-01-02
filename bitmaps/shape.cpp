//
// Created by Kevin Schmidt on 12/21/21.
//

#include "shape.hpp"

Matrix<4,4> return_1_(float t)
{
return Matrix<4,4>();
}


void Shape::draw(BitmapZ &b, Matrix<4,4> const &pov, Matrix<4,4> const &transform, float altitude, float t, Matrix<4,1> const& light_source) const
{
    Matrix<4,4> our_transform = transform * get_transform(t);
    if(triangles_)
    {
        for (Triangle const &tri: *triangles_)
        {
            Triangle temp = tri.transform(our_transform);
            //std::cout << temp.direction(Matrix<4,1>{{0},{0},{-altitude},{1}}) << '\n';
            if(temp.direction(Matrix<4,1>{{0},{0},{-altitude},{1}}) < 0)
            {
                float brightness = (temp.direction(light_source));
                b.draw_triangle(tri.transform(pov*our_transform), (brightness));
            }
        }
    }

    for (Shape const &s : sub_shapes_)
    {
        s.draw(b, pov, our_transform, altitude, t, light_source);
    }
}


void Shape::make_frames(int width, int height, Matrix<4,4> pov, float altitude, float t1, float t2, float fps,
                        char const * filename, float x1, float x2, float y1, float y2, Matrix<4,1> const & light_source)
{
    BitmapZ b(width, height);
    pov = b.map_to_image(x1, x2, y1, y2)*pov* perspective(altitude);
    int i = 1;
    for (float t = t1; t < t2; t+=(1.0/fps), i++)
    {
        b.fill_all(Color(0,0,0));

        draw(b,pov,Matrix<4,4>{},altitude,t, light_source);

        char temp[256];
        sprintf(temp, filename, i);
        std::cout << temp << std::endl;
        b.save(temp);
    }
}


