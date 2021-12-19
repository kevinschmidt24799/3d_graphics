//
// Created by Kevin Schmidt on 12/15/21.
//

#include <gtest/gtest.h>
#include "bitmaps/bitmap.hpp"
#include "bitmaps/bitmapz.hpp"
#include "bitmaps/linearization.hpp"

Color color_maker(float x, float y, float time)
{
    if(abs(x)<time/200 && abs(y)<time/200)
    {
        return Color(0, 255, 255);
    } else {
        return Color(0, 0, 0);
    }
}

TEST(bitmap, misc)
{
    Bitmap b(400,400);
    Matrix<3,3> m({{-1, -1, -1},{-1,8,-1},{-1,-1,-1}});

    for (int t = 0; t < 200; ++t)
    {
        b.fill_all(color_maker, t, rotate(t));
        Bitmap c(b);
        Bitmap d(1,1);



        d = c;

        char temp[256];
        //Bitmap * out = d.convolute(m);
        sprintf(temp, "/Users/kevinschmidt/Desktop/cppbmp1/test-%03d.bmp", t);
        d.save(temp);
    }
}

//TEST(bitmap, convolute)
//{
//    Bitmap b(300,400);
//
//    b.fill_all(color_maker, 100);
//
//    Matrix<3,3> m({{1, 1, 1},{1,1,1},{1,1,1}});
//
//    //Bitmap * out = b.convolute(m);
//
//    b.save("/Users/kevinschmidt/Desktop/convolute1");
//
//}

TEST(bitmap, line)
{
    Line3d lines[] = {
            Line3d(-1,-1,-1,1,-1,-1),
            Line3d(-1,-1,-1,-1,1,-1),
            Line3d(-1,-1,-1,-1,-1,1),

            Line3d(1,1,1,-1,1,1),
            Line3d(1,1,1,1,-1,1),
            Line3d(1,1,1,1,1,-1),

            Line3d(1,1,-1,1,-1,-1),
            Line3d(1,-1,-1,1,-1,1),
            Line3d(1,-1,1,-1,-1,1),
            Line3d(-1,-1,1,-1,1,1),
            Line3d(-1,1,1,-1,1,-1),
            Line3d(-1,1,-1,1,1,-1),

            Line3d(0,0,0,0.5,0,0, Color(255,0,0)),
            Line3d(0,0,0,0,0.5,0, Color(0,255,0)),
            Line3d(0,0,0,0,0,0.5, Color(0,0,255))
    };



    for (int t = 0; t < 360; ++t)
    {
        BitmapZ b(400,500);
        b.fill_all(Color(0,0,0));

        Matrix<4,4> transform = b.map_to_image(-2,2,-2,2)*rotate(t,1,7,3)* scale3d((float)1+t/120.0);
        for(Line3d &line : lines)
        {
            Matrix <4,1> pt1 = transform * Matrix<4,1>({{line.x1_},{line.y1_},{line.z1_},{1}});
            Matrix <4,1> pt2 = transform * Matrix<4,1>({{line.x2_},{line.y2_},{line.z2_},{1}});
            b.draw_line(pt1.data_[0][0], pt1.data_[1][0],pt2.data_[0][0], pt2.data_[1][0], line.c1_);
        }

        char temp[256];
        sprintf(temp, "/Users/kevinschmidt/Desktop/cppbmp2/test-%03d.bmp", t);
        b.save(temp);
    }


}

TEST(bitmap, increment)
{

    EXPECT_TRUE(test(0,10,0,8));
    EXPECT_TRUE(test(0,10,0,28));

    EXPECT_TRUE(test(0,10, 28,0));
    EXPECT_TRUE(test(0, -10, 0,28));

    EXPECT_TRUE(test(0,-10, 0,-28));
}

TEST(bitmap, triangle)
{
    BitmapZ b(500,500);
    b.fill_all(Color(0,0,0));
    Matrix<4,4> transform = b.map_to_image(-2,2,-2,2);
    Matrix<4,1> p1 = {{0},{1},{-1},{1}};
    Matrix<4,1> p2 = {{-1},{-1},{1},{1}};
    Matrix<4,1> p3 = {{1},{-1},{1},{1}};

    b.draw_triangle(transform*p1, transform*p2, transform*p3, Color(255,0,0), Color(0,255,0), Color(0,0,255));
    b.save("/Users/kevinschmidt/Desktop/triangle.bmp");
}




