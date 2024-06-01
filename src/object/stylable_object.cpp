/**
 * @file stylable_object.cpp
 * @author Adam Berkeš <berkeada@fit.cvut.cz>
 * @date 2023-05-08
 */

#include "stylable_object.hpp"
#include "../utils.hpp"

using namespace std;
using namespace utils;

StylableObject::Style::Style(int width_, Pixel color_)
    : width(width_), color(color_) {}

StylableObject::Style::Style(const string &src) : StylableObject::Style()
{
    const string WIDTH_NAME = "width",
                 COLOR_NAME = "color";
    vector<string> styles = split_str(src);

    for (const string &style : styles)
        if (style.rfind(WIDTH_NAME, 0) == 0)
            width = extract_int_arg(style, WIDTH_NAME, 1);
        else if (style.rfind(COLOR_NAME, 0) == 0)
            color = extract_arg(style, COLOR_NAME);
        else
            throw invalid_argument("unsupported style: " + split_str_once(style, '=').first);
}

StylableObject::StylableObject(const Style &style_)
    : style(style_) {}
