/**
 * @file elipse.cpp
 * @author Adam Berkeš <berkeada@fit.cvut.cz>
 * @date 2023-05-31
 */

#include "curve.hpp"
#include "ellipse.hpp"
#include "../utils.hpp"

#include <cmath>

using namespace std;
using namespace utils;

Ellipse::Ellipse(const StylableObject::Style &style_, const Coords &center_,
                 int radius_x_, int radius_y_)
    : StylableObject(style_), center(center_), radius_x(radius_x_), radius_y(radius_y_) {}

unique_ptr<Object> Ellipse::clone() const
{
    return make_unique<Ellipse>(*this);
}

void Ellipse::render(Image &image, const Coords &offset, const ScaleFactor &scale) const
{
    int width_half = style.width / 2,
        width_end = width_half - 1 + (style.width % 2);
    auto draw_points = [&](const double &x, const double &y)
    {
        int x_scaled = (scale.x * center.x) + offset.x,
            y_scaled = (scale.y * center.y) + offset.y;

        image.get_buffer().set_pixel(x_scaled + x, y_scaled + y, style.color);
        image.get_buffer().set_pixel(x_scaled - x, y_scaled + y, style.color);
        image.get_buffer().set_pixel(x_scaled - x, y_scaled - y, style.color);
        image.get_buffer().set_pixel(x_scaled + x, y_scaled - y, style.color);
    };

    // For each pixel of width, one ellipse is rendered
    for (int i = -width_half; i <= width_end; i++)
    {
        double r_x = (radius_x * scale.x) + i, r_x_2 = r_x * r_x,
               r_y = (radius_y * scale.y) + i, r_y_2 = r_y * r_y,
               x = 0, y = r_y,
               d1 = r_y_2 - r_x_2 * (r_y + 0.25), d2;

        while ((r_y_2 * x) < (r_x_2 * y))
        {
            draw_points(x, y);

            // Fix for thick ellipse
            if (y - x < 1)
                draw_points(x - 1, y);
            else if (x - y < 1)
                draw_points(x, y + 1);

            if (d1 < 0)
                d1 += (2 * r_y_2 * x) + (r_y_2);
            else
            {
                --y;
                d1 += r_y_2 * (2 * x + 1) - (2 * r_x_2 * y);
            }

            ++x;
        }

        d2 = (r_y_2 * pow(x + 0.5, 2)) + (r_x_2 * pow(y - 1, 2)) - (r_x_2 * r_y_2);

        while (y >= 0)
        {
            draw_points(x, y);

            // Fix for thick ellipse
            if (y - x < 1)
                draw_points(x - 1, y);
            else if (x - y < 1)
                draw_points(x, y + 1);

            if (d2 > 0)
                d2 -= (r_x * r_x) * ((2 * y) + 1);
            else
            {
                ++x;
                d2 += (2 * r_y * r_y * x) - r_x * (2 * y + 1);
            }

            --y;
        }
    }
}

unique_ptr<Object> Ellipse::parse_from_str(const string &src)
{
    const auto &[center_str, params_str] = split_str_once(src);
    const auto &[radius_x_str, params_rest] = split_str_once(params_str);
    const auto &[radius_y_str, style_str] = split_str_once(params_rest);

    return make_unique<Ellipse>(
        Ellipse(StylableObject::Style(style_str), Coords(center_str),
                extract_int_arg(radius_x_str, "radius_x"),
                extract_int_arg(radius_y_str, "radius_y")));
}
