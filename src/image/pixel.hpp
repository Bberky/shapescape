/**
 * @file pixel.hpp
 * @author Adam Berkeš <berkeada@fit.cvut.cz>
 * @date 2023-05-05
 */

#pragma once

#include <string>

/**
 * @brief Class representing a simple pixel using
 * three primary colors: red, green, and blue, each of
 * which ranges in value from 0 to 255
 */
class Pixel
{
    using bit8 = unsigned char;

    /**
     * @brief Extract specific color from hexadecimal value
     *
     * @throws std::invalid_argument color could not be extracted
     * @param hex_color Hexadecimal color value, valid forms are: #rrggbb or #rgb
     * @param color_num The number of the color to get, 0 for red,
     * 1 for green, and 2 for blue
     * @return bit8
     */
    static bit8 get_color_from_hex(const std::string &hex_color, int color_num);

public:
    bit8 r, g, b;

    /** Construct a new Pixel object with default color black */
    Pixel();

    /**
     * @brief Construct a new Pixel object
     * with the specified color
     *
     * @param red
     * @param green
     * @param blue
     */
    Pixel(bit8 red, bit8 green, bit8 blue);

    /**
     * @brief Construct a new Pixel object from hexadecimal value
     *
     * @throws std::invalid_argument invalid hexadecimal value was entered
     * @param hex_color Hexadecimal color value, valid forms are: #rrggbb or #rgb
     */
    Pixel(const std::string &hex_color);
};