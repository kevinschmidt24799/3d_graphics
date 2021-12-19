//
// Created by Kevin Schmidt on 12/18/21.
//

#include "bitmapz.hpp"
#include "bitmaps/linearization.hpp"

BitmapZ::BitmapZ(int w, int h)
    : Bitmap(w,h)
{
    z_buffer_ = new float [width_*height_];
    for (int i = 0; i < width_*height_; ++i)
    {
        z_buffer_[i] = 0;
    }
}

BitmapZ::~BitmapZ()
{
    delete[] z_buffer_;
}

void BitmapZ::set_pixel(int x, int y, float z, Color const &c)
{
    if(!(x >= 0 && x < width_))
    {
        return;
    }
    if(!(y >= 0 && y < height_))
    {
        return;
    }

    int i = (x)+width_*(y);

    if(z >= z_buffer_[i])
    {
        Bitmap::set_pixel(x,y,c);
        z_buffer_[i] = z;
    }
}

void BitmapZ::draw_triangle(Matrix<4,1> p1, Matrix<4,1> p2, Matrix<4,1> p3, Color c1, Color c2, Color c3)
{
    p1.normalize();
    p2.normalize();
    p3.normalize();

    if(p1.data_[1][0] < p2.data_[1][0])
    {
        std::swap(p1,p2);
        std::swap(c1, c2);
    }
    if(p1.data_[1][0] < p3.data_[1][0])
    {
        std::swap(p1,p3);
        std::swap(c1, c3);
    }
    if(p2.data_[1][0] < p3.data_[1][0])
    {
        std::swap(p2,p3);
        std::swap(c2, c3);
    }


    Linearization p1p2(p1.data_[1][0], p2.data_[1][0], p1.data_[0][0],p2.data_[0][0]);
    Linearization p1p3(p1.data_[1][0], p3.data_[1][0], p1.data_[0][0],p3.data_[0][0]);
    Linearization p2p3(p2.data_[1][0], p3.data_[1][0], p2.data_[0][0],p3.data_[0][0]);

    Linfloat p1p2z(p1.data_[1][0], p2.data_[1][0], p1.data_[2][0], p2.data_[2][0]);
    Linfloat p1p3z(p1.data_[1][0], p3.data_[1][0], p1.data_[2][0], p3.data_[2][0]);
    Linfloat p2p3z(p2.data_[1][0], p3.data_[1][0], p2.data_[2][0], p3.data_[2][0]);

    Linearization c1c2r_(p1.data_[1][0], p2.data_[1][0], c1.r_, c2.r_);
    Linearization c1c3r_(p1.data_[1][0], p3.data_[1][0], c1.r_, c3.r_);
    Linearization c2c3r_(p2.data_[1][0], p3.data_[1][0], c2.r_, c3.r_);
    
    Linearization c1c2g_(p1.data_[1][0], p2.data_[1][0], c1.g_, c2.g_);
    Linearization c1c3g_(p1.data_[1][0], p3.data_[1][0], c1.g_, c3.g_);
    Linearization c2c3g_(p2.data_[1][0], p3.data_[1][0], c2.g_, c3.g_);
    
    Linearization c1c2b_(p1.data_[1][0], p2.data_[1][0], c1.b_, c2.b_);
    Linearization c1c3b_(p1.data_[1][0], p3.data_[1][0], c1.b_, c3.b_);
    Linearization c2c3b_(p2.data_[1][0], p3.data_[1][0], c2.b_, c3.b_);


    while(true)
    {
        if(p1p2.d_ == p1p2.d2_)
        {
            break;
        }
        horizontal_line(p1p3.d_, p1p2.r_, p1p3.r_,
                        p1p2z.r_, p1p3z.r_,
                        Color(c1c2r_.r_, c1c2g_.r_, c1c2b_.r_),
                        Color(c1c3r_.r_, c1c3g_.r_, c1c3b_.r_));

        p1p2.next();
        p1p3.next();

        p1p2z.next();
        p1p3z.next();

        c1c2r_.next();
        c1c2g_.next();
        c1c2b_.next();

        c1c3r_.next();
        c1c3g_.next();
        c1c3b_.next();
    }
    while(true)
    {
        if(p1p3.d_ == p1p3.d2_)
        {
            break;
        }
        horizontal_line(p1p3.d_, p1p3.r_, p2p3.r_,
                        p1p3z.r_, p2p3z.r_,
                        Color(c1c3r_.r_, c1c3g_.r_, c1c3b_.r_),
                        Color(c2c3r_.r_, c2c3g_.r_, c2c3b_.r_));

        p2p3.next();
        p1p3.next();

        p1p3z.next();
        p2p3z.next();

        c1c3r_.next();
        c1c3g_.next();
        c1c3b_.next();

        c2c3r_.next();
        c2c3g_.next();
        c2c3b_.next();
    }

}

void BitmapZ::horizontal_line(int y, int x1, int x2, float z1, float z2, Color c1, Color c2)
{
    if(x2 < x1)
    {
        std::swap(x2, x1);
        std::swap(c1, c2);
        std::swap(z1, z2);
    }

    Linfloat z(x1, x2, z1, z2);

    Linearization c1c2r_(x1, x2, c1.r_, c2.r_);
    Linearization c1c2g_(x1, x2, c1.g_, c2.g_);
    Linearization c1c2b_(x1, x2, c1.b_, c2.b_);

    std::cout<<z1<<", "<<z2<<"\n";

    for (int x = x1; x <=x2 ; ++x)
    {
        set_pixel(x, y, z.r_, Color(c1c2r_.r_, c1c2g_.r_, c1c2b_.r_));
        c1c2r_.next();
        c1c2g_.next();
        c1c2b_.next();
        z.next();
    }
}
