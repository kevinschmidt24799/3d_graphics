//
// Created by Kevin Schmidt on 12/15/21.
//

#include "bitmap.hpp"
#include <unistd.h>
#include <sys/fcntl.h>
#include "linearization.hpp"

Bitmap::Bitmap(int w, int h)
{
    width_ = w;
    height_ = h;
    size_ = 4*width_*height_+138;
    pixels_ = new unsigned char[w*h*4];
}

Bitmap::~Bitmap()
{
    delete[] pixels_;
}

Bitmap::Bitmap (Bitmap const &other)
{
    width_=other.width_;
    height_=other.height_;
    size_ = other.size_;
    pixels_ = new unsigned char[width_*height_*4];
    memcpy(pixels_, other.pixels_, width_*height_*4);
}

Bitmap & Bitmap::operator=(Bitmap const &other)
{
    width_ = other.width_;
    height_=other.height_;
    size_ = other.size_;
    delete[] pixels_;
    pixels_ = new unsigned char[width_*height_*4];
    memcpy(pixels_, other.pixels_, width_*height_*4);
    return *this;
}




void Bitmap::save(std::string filename)
{
    unsigned char bmp_header[] = // All values are little-endian
            {
                    0x42, 0x4D,             // Signature 'BM'
                    0xaa, 0x00, 0x00, 0x00, // Size: 170 bytes
                    0x00, 0x00,             // Unused
                    0x00, 0x00,             // Unused
                    0x8a, 0x00, 0x00, 0x00, // Offset to image data

                    0x7c, 0x00, 0x00, 0x00, // DIB header size (124 bytes)
                    0x04, 0x00, 0x00, 0x00, // Width (4px)
                    0x02, 0x00, 0x00, 0x00, // Height (2px)
                    0x01, 0x00,             // Planes (1)
                    0x20, 0x00,             // Bits per pixel (32)
                    0x03, 0x00, 0x00, 0x00, // Format (bitfield = use bitfields | no compression)
                    0x20, 0x00, 0x00, 0x00, // Image raw size (32 bytes)
                    0x13, 0x0B, 0x00, 0x00, // Horizontal print resolution (2835 = 72dpi * 39.3701)
                    0x13, 0x0B, 0x00, 0x00, // Vertical print resolution (2835 = 72dpi * 39.3701)
                    0x00, 0x00, 0x00, 0x00, // Colors in palette (none)
                    0x00, 0x00, 0x00, 0x00, // Important colors (0 = all)
                    0x00, 0x00, 0xFF, 0x00, // R bitmask (00FF0000)
                    0x00, 0xFF, 0x00, 0x00, // G bitmask (0000FF00)
                    0xFF, 0x00, 0x00, 0x00, // B bitmask (000000FF)
                    0x00, 0x00, 0x00, 0xFF, // A bitmask (FF000000)
                    0x42, 0x47, 0x52, 0x73, // sRGB color space
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00, // Unused R, G, B entries for color space
                    0x00, 0x00, 0x00, 0x00, // Unused Gamma X entry for color space
                    0x00, 0x00, 0x00, 0x00, // Unused Gamma Y entry for color space
                    0x00, 0x00, 0x00, 0x00, // Unused Gamma Z entry for color space

                    0x00, 0x00, 0x00, 0x00, // Unknown
                    0x00, 0x00, 0x00, 0x00, // Unknown
                    0x00, 0x00, 0x00, 0x00, // Unknown
                    0x00, 0x00, 0x00, 0x00, // Unknown
            };

    bmp_header[2] = size_%256;
    bmp_header[3] = (size_>>8) % 256;
    bmp_header[4] = (size_>>16) % 256;
    bmp_header[5] = (size_>>24) % 256;

    bmp_header[18] = width_%256;
    bmp_header[19] = (width_>>8) % 256;
    bmp_header[20] = (width_>>16) % 256;
    bmp_header[21] = (width_>>24) % 256;

    bmp_header[22] = height_%256;
    bmp_header[23] = (height_>>8) % 256;
    bmp_header[24] = (height_>>16) % 256;
    bmp_header[25] = (height_>>24) % 256;

    int f2 = creat(filename.c_str(), 0666);
    write(f2, bmp_header, sizeof (bmp_header));
    write(f2, pixels_, size_-138);
    close(f2);
}



void Bitmap::set_pixel(int x, int y, Color const &c)
{
    if(!(x >= 0 && x < width_))
    {
        return;
    }
    if(!(y >= 0 && y < height_))
    {
        return;
    }

    int i = 4*(x)+4*width_*(y);

    pixels_[i] = c.b_;
    pixels_[i+1] = c.g_;
    pixels_[i+2] = c.r_;
    pixels_[i+3] = c.a_;
}

Color Bitmap::get_pixel(int x, int y) const
{
    assert(x >= 0 && x < width_);
    assert(y >= 0 && y < height_);

    int i = 4*(x)+4*width_*(y);

    return Color(pixels_[i+2], pixels_[i+1], pixels_[i], pixels_[i+3]);

}


void Bitmap::fill_all(const Color &c)
{
    for (int y = 0; y < height_; ++y)
    {
        for (int x = 0; x < width_; ++x)
        {
            set_pixel(x,y,c);
        }
    }
}



Matrix<3,3> Bitmap::image_to_map(float x1, float x2, float y1, float y2)
{
    //fat is true when image is fatter than map
    bool fat = ((float)width_/(float)height_ >= (x2-x1)/(y2-y1));
    Matrix<3,3> out;
    if(fat){
        out = translate((height_-width_)/2, 0);
        out = scale((y2-y1)/(float)height_) * out;
        out = translate(x1, y1) * out;
    } else {
        out = translate(0,(width_-height_)/2);
        out = scale((x2-x1)/(float)width_) * out;
        out = translate(x1, y1) * out;
    }
    return out;
}

Matrix<4,4> Bitmap::map_to_image(float x1, float x2, float y1, float y2)
{
    bool fat = ((float)width_/(float)height_ >= (x2-x1)/(y2-y1));
    Matrix<4,4> out;
    if(fat){
        out = translate(-x1,-y1,0);
        out = scale3d((float)height_/(y2-y1)) * out;
        out = translate((float)(width_-height_)/2, 0, 0) * out;
    } else {
        out = translate(-x1,-y1,0);
        out = scale3d((float)width_/(x2-x1)) * out;
        out = translate(0, (float)(height_-width_)/2, 0) * out;
    }
    return out;
}


void Bitmap::fill_all(Color (*fn)(float x, float y, float time), float time,Matrix<3,3> const &perspective)
{
    Matrix<3,3> m = perspective * image_to_map();
    for (int px = 0; px < width_; ++px)
    {
        for (int py = 0; py < height_; ++py)
        {
            Matrix<3,1>p({{(float)px},{(float)py},{1}});
            p = m * p;
            p.normalize();
            //std::cout << p;
            set_pixel(px, py, fn(p.data_[0][0], p.data_[1][0], time));
        }
    }
}



void Bitmap::draw_line(int x1, int y1, int x2, int y2, Color c)
{
    if( abs(x2-x1) >= abs(y2-y1) )
    {
        Linearization l (x1, x2, y1, y2);
        while(true)
        {
            set_pixel(l.d_, l.r_, c);
            if(l.d_ == l.d2_)
            {
                break;
            }
            l.next();
        }

    }else{
        Linearization l (y1, y2, x1, x2);
        while(true)
        {
            set_pixel(l.r_, l.d_, c);
            if(l.d_ == l.d2_)
            {
                break;
            }
            l.next();
        }
    }
}