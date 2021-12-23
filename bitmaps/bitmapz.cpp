//
// Created by Kevin Schmidt on 12/18/21.
//

#include "bitmapz.hpp"
#include "bitmaps/linearization.hpp"
#include <math.h>
#include "matrices/matrix.hpp"

BitmapZ::BitmapZ(int w, int h)
    : Bitmap(w,h)
{
    z_buffer_ = new float [width_*height_];
    for (int i = 0; i < width_*height_; ++i)
    {
        z_buffer_[i] = std::numeric_limits<float>::lowest();
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

//    if (x == 1010 && y == 505) {
//        std::cout << "z is " << z_buffer_[i] << '\n';
//    }

    if(z >= z_buffer_[i])
    {
        Bitmap::set_pixel(x,y,c);
        // std::cout << z_buffer_[i] <<" replaced with "<< z <<std::endl;

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

void BitmapZ::draw_triangle(Triangle t)
{
    //std::cout << t.p1_.data_[2][0] << "," << t.p2_.data_[2][0] << "," << t.p3_.data_[3][0] << '\n';
    draw_triangle(t.p1_, t.p2_, t.p3_, t.c1_, t.c2_, t.c3_);
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

    //std::cout<<z1<<", "<<z2<<"\n";

    for (int x = x1; x <=x2 ; ++x)
    {
        set_pixel(x, y, z.r_, Color(c1c2r_.r_, c1c2g_.r_, c1c2b_.r_));
        c1c2r_.next();
        c1c2g_.next();
        c1c2b_.next();
        z.next();
    }
}


Triangle Triangle::transform(Matrix<4,4> const &m) const
{
    return Triangle(m*p1_,m*p2_, m*p3_, c1_, c2_, c3_);
}

std::shared_ptr<TriangleList> disc(float r, float height, int segments, Color c1, Color c2)
{
    std::shared_ptr<TriangleList> out(new TriangleList);

    Matrix<4,1> o1({{0},{0},{height/2},{1}});
    Matrix<4,1> p11({{r*(float)cos(M_PI/segments*0)},{r*(float)sin(M_PI/segments*0)},{height/2},{1}});
    Matrix<4,1> p12({{r*(float)cos(M_PI/segments*1)},{r*(float)sin(M_PI/segments*1)},{height/2},{1}});

    Matrix<4,1> o2({{0},{0},{-height/2},{1}});
    Matrix<4,1> p21({{r*(float)cos(M_PI/segments*0.5)},{r*(float)sin(M_PI/segments*0.5)},{-height/2},{1}});
    Matrix<4,1> p22({{r*(float)cos(M_PI/segments*1.5)},{r*(float)sin(M_PI/segments*1.5)},{-height/2},{1}});

    for (int i = 0; i < 2*segments; ++i)
    {
        out->push_back(Triangle(o1, p11, p12, c1));
        out->push_back(Triangle(o2, p21, p22,  c1));
        c1.invert();

        out->push_back(Triangle(p11, p12,p21, c2));
        c2.invert();

        out->push_back(Triangle(p21, p22, p12, c2));
        c2.invert();


        o1 = rotate(180.0/segments, 0,0,1)*o1;
        o2 = rotate(180.0/segments, 0,0,1)*o2;
        p11 = rotate(180.0/segments, 0,0,1)*p11;
        p12 = rotate(180.0/segments, 0,0,1)*p12;
        p21 = rotate(180.0/segments, 0,0,1)*p21;
        p22 = rotate(180.0/segments, 0,0,1)*p22;

    }
    return out;
}

void BitmapZ::fill_all(const Color &c)
{
    Bitmap::fill_all(c);
    for (int i = 0; i < width_ * height_; ++i)
    {
        z_buffer_[i] = std::numeric_limits<float>::lowest();
    }
}