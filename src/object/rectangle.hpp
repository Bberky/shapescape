/**
 * @file rectangle.hpp
 * @author Adam Berkeš <berkeada@fit.cvut.cz>
 * @date 2023-05-13
 */

#pragma once

#include "stylable_object.hpp"

/**
 * @brief Rectangle object represented by two 2D vectors,
 * its upper left and lower right corner
 */
class Rectangle : public StylableObject
{
    Coords start, end;

public:
    /**
     * @brief Construct a new Rectangle object with given parameters
     *
     * @param style_ Optional width and color of the rectangle
     * @param start_ Upper left corner of the rectangle
     * @param end_ Lower right corner of the rectangle
     */
    Rectangle(const StylableObject::Style &style_, const Coords &start_, const Coords &end_);

    std::unique_ptr<Object> clone() const override;

    /**
     * @brief Render rectangle with given offset and scale into image by
     * by forming 4 lines that connect at right angle
     *
     * @param image Image the rectangle should be rendered into
     * @param offset Offset of the rectangle from origin (0,0)
     * @param scale Scale of the rectangle
     */
    void render(Image &image, const Coords &offset, const ScaleFactor &scale) const override;

    /**
     * @brief Parse the rectangle from given string
     *
     * @throws std::invalid_argument If the string couldn't be parsed
     * @param src String in the form "((0,0);(100,100)) width=34 color=#abcdef"
     * @return std::unique_ptr<Object>
     */
    static std::unique_ptr<Object> parse_from_str(const std::string &src);
};
