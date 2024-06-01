/**
 * @file hexagon.cpp
 * @author Adam Berkeš <berkeada@fit.cvut.cz>
 * @date 2023-06-03
 */

#include "regular_polygon.hpp"
#include "line.hpp"
#include "../utils.hpp"

#include <cmath>

using namespace std;
using namespace utils;

RegularPolygon::RegularPolygon(const StylableObject::Style &style_, const Coords &center_,
                               int n_sides_, int side_)
    : StylableObject(style_), center(center_), n_sides(n_sides_), side(side_) {}

unique_ptr<Object> RegularPolygon::clone() const
{
    return make_unique<RegularPolygon>(*this);
}

void RegularPolygon::render(Image &image, const Coords &offset, const ScaleFactor &scale) const
{
    const double FULL_ANGLE = 360.0;
    const double HALF_ANGLE = FULL_ANGLE / 2.0;
    const double BASE_ANGLE = FULL_ANGLE / n_sides;

    double angle = ((n_sides - 2) * HALF_ANGLE) / (n_sides * 2);
    Coords start(cos(angle * M_PI / HALF_ANGLE) * side + center.x,
                 sin(angle * M_PI / HALF_ANGLE) * side + center.y);

    for (int i = 0; i < n_sides; i++)
    {
        angle -= BASE_ANGLE;
        Coords next(cos(angle * M_PI / HALF_ANGLE) * side + center.x,
                    sin(angle * M_PI / HALF_ANGLE) * side + center.y);
        Line(style, start, next).render(image, offset, scale);
        start = next;
    }
}

unique_ptr<Object> RegularPolygon::parse_from_str(const string &src)
{
    const auto &[center_str, params] = split_str_once(src);
    const auto &[n_sides_str, params_rest] = split_str_once(params);
    const auto &[side_str, style_str] = split_str_once(params_rest);

    return make_unique<RegularPolygon>(
        RegularPolygon(StylableObject::Style(style_str),
                       Coords(center_str), extract_int_arg(n_sides_str, "n_sides", 3), extract_int_arg(side_str, "side")));
}
