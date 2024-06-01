/**
 * @file image.cpp
 * @author Adam Berkeš <berkeada@fit.cvut.cz>
 * @date 2023-05-06
 */

#include "image.hpp"

#include <stdexcept>

using namespace std;

Image::ImageBuffer::ImageBuffer(int width, int height, const Pixel &bg_color)
try : data(height, vector<Pixel>(width, bg_color))
{
}
catch (...)
{
    throw invalid_argument(
        "invalid image resolution: " + to_string(width) + 'x' + to_string(height));
}

bool Image::ImageBuffer::set_pixel(size_t x, size_t y, Pixel pixel)
{
    if (x >= data[0].size() || y >= data.size())
        return false;

    data[y][x] = pixel;

    return true;
}

Pixel &Image::ImageBuffer::operator()(size_t x, size_t y)
{
    return data[y][x];
}

Pixel Image::ImageBuffer::operator()(size_t x, size_t y) const
{
    return data[y][x];
}

Image::Image(int width_, int height_, const Pixel &bg_color)
    : buffer(width_, height_, bg_color), width(width_), height(height_) {}

int Image::get_width() const { return width; }

int Image::get_height() const { return height; }

long Image::get_size() const { return width * height * sizeof(Pixel); }

Image::ImageBuffer &Image::get_buffer()
{
    return buffer;
}

const Image::ImageBuffer &Image::get_buffer() const
{
    return buffer;
}
