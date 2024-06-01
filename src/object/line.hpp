/**
 * @file line.hpp
 * @author Adam Berkeš <berkeada@fit.cvut.cz>
 * @date 2023-05-06
 */

#pragma once

#include "stylable_object.hpp"

/**
 * @brief Two-dimensional Line given by two endpoints and
 * its thickness and color
 */
class Line : public StylableObject
{
    /** First endpoint of the line */
    Coords start;
    /** Second endpoint of the line */
    Coords end;

    /**
     * @brief Draw a one-pixel thick line into image using Bresenham's line
     * drawing alogrithm
     *
     * @param image Image the line should be rendered into
     * @param v1 First endpoint of the line
     * @param v2 Second endpoint of the line
     */
    void draw_line(Image &image, const Coords &v1, const Coords &v2) const;

public:
    /**
     * @brief Construct a new Line object with given parameters
     *
     * @param style_ Optional width and color of the line
     * @param start_ First endpoint of the line
     * @param end_ Second endpoint of the line
     */
    Line(const StylableObject::Style &style_, const Coords &start_, const Coords &end_);

    std::unique_ptr<Object> clone() const override;

    /**
     * @brief Render line with given offset and scale into image
     * using Bresenham's line drawing algorithm
     *
     * <a href="https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm">Bresenham's line algorithm</a>
     * @param image Image the line should be rendered into
     * @param offset Offset of the line from origin (0,0)
     * @param scale Scale of the line
     */
    void render(Image &image, const Coords &offset, const ScaleFactor &scale) const override;

    /**
     * @brief Parse the line from given string
     *
     * @throws std::invalid_argument If the string couldn't be parsed
     * @param src String in the form "((0,0);(100,100)) width=5 color=#ffffff"
     * @return std::unique_ptr<Object>
     */
    static std::unique_ptr<Object> parse_from_str(const std::string &src);

    /**
     * @brief Calculate the slope of this line
     *
     * @return double
     */
    double calc_slope() const;
};
