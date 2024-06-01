/**
 * @file rectangle.cpp
 * @author Adam Berkeš <berkeada@fit.cvut.cz>
 * @date 2023-05-13
 */

#include "line.hpp"
#include "rectangle.hpp"
#include "../utils.hpp"

#include <array>

using namespace std;
using namespace utils;

Rectangle::Rectangle(const StylableObject::Style &style_, const Coords &start_, const Coords &end_)
    : StylableObject(style_), start(start_), end(end_)
{
}

unique_ptr<Object> Rectangle::clone() const
{
    return make_unique<Rectangle>(*this);
}

void Rectangle::render(Image &image, const Coords &offset,
                       const ScaleFactor &scale) const
{
    array<Line, 4> lines{
        // Upper line
        Line(style, start - Coords(style.width / 2, 0),
             Coords(end.x + style.width / 2 + style.width % 2, start.y)),
        // Left line
        Line(style, start, Coords(start.x, end.y)),
        // Lower line
        Line(style, Coords(start.x - style.width / 2, end.y),
             end + Coords(style.width / 2 + style.width % 2, 0)),
        // Right line
        Line(style, Coords(end.x, start.y), end)};

    for (const Line &line : lines)
        line.render(image, offset, scale);
}

unique_ptr<Object> Rectangle::parse_from_str(const string &src)
{
    const auto &[position_str, style_str] = split_str_once(src);
    vector<Coords> vertices = parse_vertices(position_str, 2, 2);

    return make_unique<Rectangle>(
        Rectangle(StylableObject::Style(style_str), vertices[0], vertices[1]));
}
