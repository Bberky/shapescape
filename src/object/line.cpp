/**
 * @file line.cpp
 * @author Adam Berkeš <berkeada@fit.cvut.cz>
 * @date 2023-05-06
 */

#include "line.hpp"
#include "../utils.hpp"

#include <sstream>

using namespace std;
using namespace utils;

Line::Line(const StylableObject::Style &style_, const Coords &start_, const Coords &end_)
    : StylableObject(style_), start(start_), end(end_) {}

void Line::draw_line(Image &image, const Coords &v1, const Coords &v2) const
{
    int x0 = v1.x, x1 = v2.x, y0 = v1.y, y1 = v2.y,
        dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1,
        dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1,
        err = dx + dy;

    while (x0 != x1 || y0 != y1)
    {
        image.get_buffer().set_pixel(x0, y0, style.color);

        int e2 = 2 * err;

        if (e2 >= dy)
        {
            err += dy;
            x0 += sx;
        }
        else if (e2 <= dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

unique_ptr<Object> Line::clone() const
{
    return make_unique<Line>(*this);
}

void Line::render(Image &image, const Coords &offset, const ScaleFactor &scale) const
{
    int x0 = (scale.x * start.x) + offset.x,
        x1 = (scale.x * end.x) + offset.x,
        y0 = (scale.y * start.y) + offset.y,
        y1 = (scale.y * end.y) + offset.y;

    double slope = calc_slope();
    int width_half = style.width / 2;
    int width_end = width_half - 1 + (style.width % 2);

    // Iterate once for every pixel of width,
    // distributing thickness of the line evenly
    for (int i = -width_half; i <= width_end; i++)
        if (abs(slope) <= 1)
            draw_line(image, Coords(x0, y0 + i), Coords(x1, y1 + i));
        else
            draw_line(image, Coords(x0 + i, y0), Coords(x1 + i, y1));
}

unique_ptr<Object> Line::parse_from_str(const string &src)
{
    const auto &[position_str, style_str] = split_str_once(src);
    vector<Coords> vertices = parse_vertices(position_str, 2, 2);

    return make_unique<Line>(Line(StylableObject::Style(style_str), vertices[0], vertices[1]));
}

double Line::calc_slope() const
{
    // Rise over run
    return end.x - start.x == 0
               ? numeric_limits<double>::max()
               : ((end.y - start.y) / static_cast<double>(end.x - start.x));
}
