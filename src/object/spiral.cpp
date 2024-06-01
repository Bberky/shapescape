/**
 * @file spiral.cpp
 * @author Adam Berkeš <berkeada@fit.cvut.cz>
 * @date 2023-06-01
 */

#include "curve.hpp"
#include "spiral.hpp"
#include "../utils.hpp"

#include <array>
#include <cmath>
#include <iostream>

using namespace std;
using namespace utils;

Spiral::Spiral(const StylableObject::Style &style_, const Coords &center_, int rotations_)
    : StylableObject(style_), center(center_), rotations(rotations_)
{
    if (rotations <= 0)
        throw invalid_argument("number of rotations for spiral has to be at least 1");
}

unique_ptr<Object> Spiral::clone() const
{
    return make_unique<Spiral>(*this);
}

void Spiral::render(Image &image, const Coords &offset, const ScaleFactor &scale) const
{
    // Golden ratio
    const double PHI = (1 + sqrt(5)) / 2;
    const int R_BASE = 4 * style.width;
    bool is_upper = true;

    for (int i = 0; i < 2 * rotations; i++)
    {
        array<Coords, 3> curve_points;

        if (is_upper)
        {
            curve_points[0] = center - Coords(i * R_BASE, 0);
            curve_points[2] = center + Coords((i + 1) * R_BASE, 0);
            curve_points[1] = Coords((curve_points[0].x + curve_points[2].x) / 2,
                                     center.y + i * R_BASE * (PHI * PHI));
        }
        else
        {
            curve_points[0] = center + Coords(i * R_BASE, 0);
            curve_points[2] = center - Coords((i + 1) * R_BASE, 0);
            curve_points[1] = Coords((curve_points[0].x + curve_points[2].x) / 2,
                                     center.y - i * R_BASE * (PHI * PHI));
        }

        Curve(style, curve_points).render(image, offset, scale);
        is_upper = !is_upper;
    }
}

unique_ptr<Object> Spiral::parse_from_str(const string &src)
{
    const auto &[center_str, params_str] = split_str_once(src);
    const auto &[rotations_str, style_str] = split_str_once(params_str);
    int rotations = extract_int_arg(rotations_str, "rotations");

    return make_unique<Spiral>(
        Spiral(StylableObject::Style(style_str), Coords(center_str), rotations));
}
