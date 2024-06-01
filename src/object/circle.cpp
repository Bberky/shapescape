/**
 * @file circle.cpp
 * @author Adam Berkeš <berkeada@fit.cvut.cz>
 * @date 2023-05-07
 */

#include "circle.hpp"
#include "../utils.hpp"

using namespace std;
using namespace utils;

Circle::Circle(const StylableObject::Style &style_, Coords center_, int radius_)
    : StylableObject(style_), center(center_), radius(radius_) {}

void Circle::draw_octants(Image &image, const Coords &c, const Coords &d,
                          int x_shit, int y_shift) const
{
    const Pixel &color = style.color;
    int x0 = c.x, y0 = c.y,
        x = d.x, y = d.y;

    image.get_buffer().set_pixel((x + x_shit) + x0, (y + y_shift) + y0, color);
    image.get_buffer().set_pixel((y + x_shit) + x0, (x + y_shift) + y0, color);
    image.get_buffer().set_pixel(-(x + x_shit) + x0, (y + y_shift) + y0, color);
    image.get_buffer().set_pixel(-(y + x_shit) + x0, (x + y_shift) + y0, color);
    image.get_buffer().set_pixel(-(x + x_shit) + x0, -(y + y_shift) + y0, color);
    image.get_buffer().set_pixel(-(y + x_shit) + x0, -(x + y_shift) + y0, color);
    image.get_buffer().set_pixel((x + x_shit) + x0, -(y + y_shift) + y0, color);
    image.get_buffer().set_pixel((y + x_shit) + x0, -(x + y_shift) + y0, color);
}

void Circle::draw_circle(Image &image, int x0, int y0, int r) const
{
    int x = 0,
        y = r,
        d = 3 - 2 * r;

    while (x <= y)
    {
        draw_octants(image, Coords(x0, y0), Coords(x, y));

        // Fix for dead pixels in thicc circles
        if (x - y < 1)
            draw_octants(image, Coords(x0, y0), Coords(x, y), 1, 0);

        if (d < 0)
            d += 4 * x + 6;
        else
        {
            d += 4 * (x - y) + 10;
            --y;
        }

        ++x;
    }
}

unique_ptr<Object>
Circle::clone() const
{
    return make_unique<Circle>(*this);
}

void Circle::render(Image &image, const Coords &offset,
                    const ScaleFactor &scale) const
{
    int x0 = (scale.x * center.x) + offset.x,
        y0 = (scale.y * center.y) + offset.y,
        r = radius * ((abs(scale.x) + abs(scale.y)) / 2);

    for (int i = -(style.width / 2); i <= style.width / 2; i++)
        draw_circle(image, x0, y0, r + i);
}

unique_ptr<Object> Circle::parse_from_str(const string &src)
{
    const auto &[center_str, params_str] = split_str_once(src);
    const auto &[radius_str, style_str] = split_str_once(params_str);

    return make_unique<Circle>(Circle(StylableObject::Style(style_str),
                                      Coords(center_str), extract_int_arg(radius_str, "radius")));
}
