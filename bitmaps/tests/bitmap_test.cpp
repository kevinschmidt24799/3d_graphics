//
// Created by Kevin Schmidt on 12/15/21.
//

#include <gtest/gtest.h>
#include "bitmaps/bitmap.hpp"
#include "bitmaps/bitmapz.hpp"
#include "bitmaps/linearization.hpp"
#include <vector>
#include "bitmaps/shape.hpp"

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

        Matrix<4,4> transform = b.map_to_image(-2,2,-2,2)*perspective(1.8)*rotate(t,1,7,3);
        for(Line3d &line : lines)
        {
            Matrix <4,1> pt1 = (transform * Matrix<4,1>({{line.x1_},{line.y1_},{line.z1_},{1}})).normalize();
            Matrix <4,1> pt2 = (transform * Matrix<4,1>({{line.x2_},{line.y2_},{line.z2_},{1}})).normalize();
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
    EXPECT_TRUE(test(0,0,2,2));
}

TEST(bitmap, triangle)
{
    BitmapZ b(500,500);
    b.fill_all(Color(0,0,0));
    Matrix<4,4> transform = b.map_to_image(-2,2,-2,2);
    Matrix<4,1> p1 = {{0},{1},{1},{1}};
    Matrix<4,1> p2 = {{-1},{-1},{-1},{1}};
    Matrix<4,1> p3 = {{1},{-1},{-1},{1}};

    b.draw_triangle(transform*p1, transform*p2, transform*p3, Color(255,0,0), Color(0,255,0), Color(0,0,255));
    b.save("/Users/kevinschmidt/Desktop/triangle.bmp");
}

TEST(bitmap, funny_triangle)
{
    BitmapZ b(500,500);
    b.fill_all(Color(0,0,0));
    Matrix<4,4> transform = b.map_to_image(-2,2,-2,2);
    Matrix<4,1> p1 = {{0},{1},{-1},{1}};
    Matrix<4,1> p2 = {{-1},{-1},{1},{1}};
    Matrix<4,1> p3 = {{1},{-1},{1},{1}};
    Matrix<4,1> p4 = {{0},{0},{1},{1}};

    for (int t = 0; t < 360; ++t)
    {
        BitmapZ b(500,500);
        b.fill_all(Color(0,0,0));

        Matrix<4,4> transform = b.map_to_image(-2,2,-2,2)*rotate(t,1,0,0);
        b.draw_triangle(transform*p1, transform*p2, transform*p3, Color(255,0,0), Color(0,255,0), Color(0,0,255));
        b.draw_triangle(transform*p1, transform*p2, transform*p4, Color(255,0,0), Color(0,255,0), Color(0,0,255));
        b.draw_triangle(transform*p1, transform*p3, transform*p4, Color(255,0,0), Color(0,255,0), Color(0,0,255));
        b.draw_triangle(transform*p4, transform*p2, transform*p3, Color(255,0,0), Color(0,255,0), Color(0,0,255));

        char temp[256];
        sprintf(temp, "/Users/kevinschmidt/Desktop/cppbmp3/test-%03d.bmp", t);
        b.save(temp);
    }

}

TEST(bitmap, pyramid_list)
{
    BitmapZ b(500,500);
    b.fill_all(Color(0,0,0));
    Matrix<4,4> transform = b.map_to_image(-2,2,-2,2);
    Matrix<4,1> p1 = {{0},{1},{-1},{1}};
    Matrix<4,1> p2 = {{-1},{-1},{1},{1}};
    Matrix<4,1> p3 = {{1},{-1},{1},{1}};
    Matrix<4,1> p4 = {{0},{0},{1},{1}};

    TriangleList pyramid;

    pyramid.push_back(Triangle (p1, p2, p3, Color(255, 0, 0)));
    pyramid.push_back(Triangle (p4, p2, p3, Color(0, 255, 0)));
    pyramid.push_back(Triangle (p1, p4, p3, Color(0, 0, 255)));
    pyramid.push_back(Triangle (p1, p2, p4, Color(255, 0, 255)));

    for (int t = 0; t < 360; ++t)
    {
        BitmapZ b(500,500);
        b.fill_all(Color(0,0,0));

        Matrix<4,4> transform = b.map_to_image(-2,2,-2,2)*rotate(t,1,0,0);
        for (Triangle const &t : pyramid)
        {
            b.draw_triangle(t.transform(transform));
        }
        char temp[256];
        sprintf(temp, "/Users/kevinschmidt/Desktop/cppbmp4/test-%03d.bmp", t);
        b.save(temp);
    }
}


TEST(bitmap, disc)
{
    std::shared_ptr<TriangleList> triangles = disc(0.5, 0.1, 8);

    for (int t = 0; t < 360; ++t)
    {
        BitmapZ b(500,500);
        b.fill_all(Color(0,0,0));

        Matrix<4,4> view = b.map_to_image(-2,2,-2,2)*perspective(3);

        Matrix<4,4> transform = translate(0,0,(float)t/-130)*rotate(2*t,1,1,0);

        for (Triangle const &t : *triangles)
        {
            b.draw_triangle(t.transform(view*transform));
        }
        char temp[256];
        sprintf(temp, "/Users/kevinschmidt/Desktop/cppbmp4/test-%03d.bmp", t);
        std::cout << temp << std::endl;
        b.save(temp);
    }
}


TEST(bitmap, shape)
{
    Shape s(disc(2,0.2,6),
            [](float t)
            {
                return motion_linear(t, Matrix<4,1>{{1},{1},{-1},{0}}, 0, 2.5)
                      *motion_linear(t, Matrix<4,1>{{1},{1},{-1},{0}}*-1, 2.5, 5)
                      *motion_rotate(t, 360/2.5, 1,1,1,0,2.5)
                      *rotate(90,1,0,0);
            });

    s.make_frames(1700,1000, perspective(5),0,5, 60, "/Users/kevinschmidt/Desktop/cppbmp5/test-%03d.bmp", -2, 2, -2, 2);

}

TEST(bitmap, motion_linear)
{
    for (float t = 1; t < 5; t+=1.0/60)
    {
        std::cout << motion_linear(t, Matrix<4,1>{{1},{1},{-3},{0}}, 0, 5);
    }
}


TEST(bitmap, crazy_shapes)
{
    Shape s(nullptr,
            [](float t)
            {
                return motion_linear(t, Matrix<4,1>{{0},{-2},{2},{0}}, 0, 2)
                       *motion_linear(t, Matrix<4,1>{{-2},{2},{0},{0}}, 2, 4)
                       *motion_linear(t, Matrix<4,1>{{0},{-2},{-2},{0}}, 4, 6)
                       *motion_linear(t, Matrix<4,1>{{2},{2},{0},{0}}, 6, 8)
                       *translate(2.5,2.5,-2.5)
                       *motion_rotate(t, 360/2.5, 1,1,1,0,2)
                       *motion_rotate(t, 360/2.5, 1,1,1,4,8)
                       *rotate(90,1,0,0);
            });

    auto gear = disc(1,0.2,6);
    s.sub_shapes_.emplace_back(Shape(gear, [](float t)
        {
            return motion_rotate(t, 180, 1,0,0,0,8)
                  *translate(1,0,0)
                  *rotate(-90,0,1,0);
        }));
    s.sub_shapes_.emplace_back(Shape(gear, [](float t)
    {
        return motion_rotate(t, -180, 1,0,0,0,8)
               *translate(-1,0,0)
               *rotate(90,0,1,0);
    }));
    s.sub_shapes_.emplace_back(Shape(gear, [](float t)
    {
        return motion_rotate(t, -180, 0,1,0,0,8)
               *translate(0,1,0)
               *rotate(-90,1,0,0);
    }));
    s.sub_shapes_.emplace_back(Shape(gear, [](float t)
    {
        return motion_rotate(t, 180, 0,1,0,0,8)
               *translate(0,-1,0)
               *rotate(90,1,0,0);
    }));
    s.make_frames(3440,1440, scale3d(3)*perspective(10),0,8, 60, "test-%03d.bmp", -2, 2, -2, 2);

}