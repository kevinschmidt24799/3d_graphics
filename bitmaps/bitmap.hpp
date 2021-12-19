//
// Created by Kevin Schmidt on 12/15/21.
//

#ifndef CLASSES_BITMAP_H
#define CLASSES_BITMAP_H

#include <string>
#include "color.hpp"
#include "matrices/matrix.hpp"

class Bitmap
{
public:

    int width_;
    int height_;
    int size_;
    unsigned char* pixels_;

    Bitmap(int w, int h);
    ~Bitmap();
    Bitmap & operator=(Bitmap const &other);

    Bitmap(Bitmap const &other);



    void save(std::string filename);
    void set_pixel(int x, int y, Color const &c);
    Color get_pixel(int x, int y) const;
    void fill_all(Color const &c);

    Matrix<4,4> map_to_image(float x1 = -1, float x2 = 1, float y1 = -1, float y2 = 1);
    Matrix<3,3> image_to_map(float x1 = -1, float x2 = 1, float y1 = -1, float y2 = 1);


    void fill_all(Color (*fn)(float x, float y, float time), float time=0, Matrix<3,3> const &perspective=Matrix<3,3>());

    void draw_line(int x1, int y1, int x2, int y2, Color c = Color(255,255,255));


    //template<int ROWS, int COLUMNS>
    //Bitmap * convolute(Matrix<ROWS, COLUMNS> const &m);

};

struct Line3d
{
    float x1_, x2_, y1_, y2_, z1_, z2_;
    Color c1_, c2_;

    Line3d(float x1,float y1,float z1,float x2,float y2,float z2,
           Color c1=Color(255,255,255), Color c2 = Color(255,255,255))
       : x1_(x1), x2_(x2), y1_(y1), y2_(y2), z1_(z1), z2_(z2)
       , c1_(c1), c2_(c2)
    {
    }
};

/*
template<int ROWS, int COLUMNS>
Bitmap * Bitmap::convolute(Matrix<ROWS, COLUMNS> const &m)
{
    static_assert(ROWS % 2 == 1);
    static_assert(COLUMNS % 2 == 1);
    assert(width_ >= COLUMNS);
    assert(height_ >= ROWS);

    float sum = 0;
    for (int i = 0; i < ROWS; ++i)
    {
        for (int j = 0; j < COLUMNS; ++j)
        {
            sum += m.data_[i][j];
        }
    }

    if(abs(sum) < 0.001) sum = 1;

    int yoffset = ROWS/2;
    int xoffset = COLUMNS/2;

    Bitmap * out = new Bitmap(width_-COLUMNS+1,height_-ROWS+1);

    for (int x = xoffset; x < width_-xoffset; ++x)
    {
        for (int y = yoffset; y < height_-yoffset; ++y)
        {
            float r = 0;
            float g = 0;
            float b = 0;
            for (int i = 0; i < ROWS; ++i)
            {
                for (int j = 0; j < COLUMNS; ++j)
                {
                    Color c = get_pixel(x-xoffset+j, y-yoffset+i);
                    r+= c.r_*m.data_[i][j];
                    g+= c.g_*m.data_[i][j];
                    b+= c.b_*m.data_[i][j];
                }
            }
            r/= sum;
            g/= sum;
            b/= sum;
            if(r < 0) r = 0;
            if(r > 255) r = 255;
            if(g < 0) g = 0;
            if(g > 255) g = 255;
            if(b < 0) b = 0;
            if(b > 255) b = 255;
            out->set_pixel(x-xoffset, y-yoffset, Color((int)(r), (int)(g), (int)(b)));
        }
    }
    return out;
}
*/
#endif //CLASSES_BITMAP_H
