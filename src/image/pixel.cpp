/**
 * @file pixel.cpp
 * @author Adam Berkeš <berkeada@fit.cvut.cz>
 * @date 2023-05-05
 */

#include "pixel.hpp"

#include <algorithm>
#include <stdexcept>

using namespace std;

Pixel::bit8 Pixel::get_color_from_hex(const string &hex_color, int color_num)
{
    invalid_argument err = invalid_argument("invalid hex color entered: " + hex_color);

    if (hex_color.length() != 7 && hex_color.length() != 4)
        throw err;

    int shift = hex_color.length() == 4 ? 1 : 2;
    string color_substr = hex_color.substr(1 + (color_num * shift), shift);

    if (!all_of(color_substr.begin(), color_substr.end(), [](char c)
                { return isxdigit(c); }))
        throw err;

    try
    {
        return stoul(color_substr + (shift == 2 ? "" : color_substr), nullptr, 16);
    }
    catch (...)
    {
        throw err;
    }
}

Pixel::Pixel() : Pixel(0, 0, 0) {}

Pixel::Pixel(bit8 red, bit8 green, bit8 blue) : r(red), g(green), b(blue) {}

Pixel::Pixel(const string &hex_color)
    : r(get_color_from_hex(hex_color, 0)),
      g(get_color_from_hex(hex_color, 1)),
      b(get_color_from_hex(hex_color, 2)) {}
