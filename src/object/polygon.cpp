/**
 * @file polygon.cpp
 * @author Adam Berkeš <berkeada@fit.cvut.cz>
 * @date 2023-06-01
 */

#include "line.hpp"
#include "polygon.hpp"
#include "../utils.hpp"

using namespace std;
using namespace utils;

Polygon::Polygon(const StylableObject::Style &style_,
                 const vector<Coords> &vertices_)
    : StylableObject(style_), vertices(vertices_)
{
    if (vertices.size() < 3 || !check_polygon())
        throw invalid_argument("invalid polygon entered");
}

bool Polygon::check_polygon() const
{
    vector<double> slopes;

    for (size_t i = 0; i < vertices.size() - 1; i++)
        slopes.push_back(Line(style, vertices[i], vertices[i + 1]).calc_slope());

    slopes.push_back(Line(style, vertices[vertices.size() - 1], vertices[0]).calc_slope());

    for (size_t i = 0; i < slopes.size() - 1; i++)
        if (abs(slopes[i] - slopes[i + 1]) <= numeric_limits<double>::epsilon())
            return false;

    return true;
}

unique_ptr<Object> Polygon::clone() const
{
    return make_unique<Polygon>(*this);
}

void Polygon::render(Image &image, const Coords &offset, const ScaleFactor &scale) const
{
    for (size_t i = 0; i <= vertices.size() - 2; i++)
        Line(style, vertices[i], vertices[i + 1]).render(image, offset, scale);

    Line(style, vertices[vertices.size() - 1], vertices[0]).render(image, offset, scale);
}

unique_ptr<Object> Polygon::parse_from_str(const string &src)
{
    const auto &[vertices_str, style_str] = split_str_once(src);
    vector<Coords> vertices = parse_vertices(vertices_str, 3);

    return make_unique<Polygon>(Polygon(StylableObject::Style(style_str), vertices));
}
