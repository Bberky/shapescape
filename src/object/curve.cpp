/**
 * @file curve.cpp
 * @author Adam Berkeš <berkeada@fit.cvut.cz>
 * @date 2023-06-01
 */

#include "curve.hpp"
#include "../utils.hpp"

#include <cmath>

using namespace std;
using namespace utils;

Curve::Curve(const StylableObject::Style &style_, const array<Coords, 3> &control_points_)
    : StylableObject(style_), control_points(control_points_) {}

unique_ptr<Object> Curve::clone() const
{
    return make_unique<Curve>(*this);
}

void Curve::render(Image &image, const Coords &offset, const ScaleFactor &scale) const
{
    const double T_INC = 0.001;
    int width_half = style.width / 2,
        width_end = width_half - 1 + (style.width % 2);
    // Standard quadratic Bezier curve equation
    auto curve_fn = [&](double t, int x0, int x1, int x2)
    {
        return (pow(1 - t, 2) * x0) + ((1 - t) * 2 * t * x1) + (t * t * x2);
    };

    // Draw separate curve for each pixel of width
    for (int i = -width_half; i <= width_end; i++)
    {

        int x0 = (scale.x * control_points[0].x) + offset.x,
            x1 = (scale.x * control_points[1].x) + offset.x,
            x2 = (scale.x * control_points[2].x) + offset.x,
            y0 = (scale.y * control_points[0].y) + offset.y,
            y1 = (scale.y * control_points[1].y) + offset.y,
            y2 = (scale.y * control_points[2].y) + offset.y;

        if (abs(x2 - x0) < abs(y2 - y0))
        {
            if ((x0 - x1) < 0)
                x1 -= i;
            else
                x1 += i;
            y0 += i;
            y2 -= i;
        }
        else
        {
            if ((y0 - y1) < 0)
                y1 -= i;
            else
                y1 += i;
            x0 += i;
            x2 -= i;
        }

        double t = T_INC;
        double x = curve_fn(t, x0, x1, x2),
               y = curve_fn(t, y0, y1, y2);

        while (t < 1)
        {
            image.get_buffer().set_pixel(x, y, style.color);
            t += T_INC;
            x = curve_fn(t, x0, x1, x2);
            y = curve_fn(t, y0, y1, y2);
        }
    }
}

unique_ptr<Object> Curve::parse_from_str(const string &src)
{
    const auto &[position_str, style_str] = split_str_once(src);
    vector<Coords> control_points = parse_vertices(position_str, 3, 3);

    return make_unique<Curve>(
        Curve(StylableObject::Style(style_str),
              array{control_points[0], control_points[1], control_points[2]}));
}
