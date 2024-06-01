/**
 * @file hexagon.hpp
 * @author Adam Berkeš <berkeada@fit.cvut.cz>
 * @date 2023-06-03
 */

#pragma once

#include "stylable_object.hpp"

/**
 * @brief Regular polygon given by center, number of sides and
 * length of a side
 */
class RegularPolygon : public StylableObject
{
    Coords center;
    int n_sides, side;

public:
    /**
     * @brief Construct a new Regular Polygon object with given parameters
     *
     * @param style_ Optional width and color of the polygon
     * @param center_ Center of the polygon
     * @param n_sides_ Number of sides of the polygon
     * @param side_ Length of one side of the polygon
     */
    RegularPolygon(const StylableObject::Style &style_, const Coords &center_,
                   int n_sides_, int side_);

    std::unique_ptr<Object> clone() const override;

    /**
     * @brief Render polygon with given offset and scale into image by constructing
     * consecutive lines of same length which form a regular polygon
     *
     * @param image Image the polygon should be rendered into
     * @param offset Offset from the origin (0,0)
     * @param scale Scale of the polygon
     */
    void render(Image &image, const Coords &offset, const ScaleFactor &scale) const override;

    /**
     * @brief Parse the polygon from given string
     *
     * @throws std::invalid_argument If the string couldn't be parsed
     * @param src String in the form "(100,100) n_sides=8 side=50 width=10 color=#f00"
     * @return std::unique_ptr<Object>
     */
    static std::unique_ptr<Object> parse_from_str(const std::string &src);
};
