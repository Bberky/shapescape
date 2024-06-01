/**
 * @file spiral.hpp
 * @author Adam Berkeš <berkeada@fit.cvut.cz>
 * @date 2023-06-01
 */

#pragma once

#include "stylable_object.hpp"

/**
 * @brief Spiral given by its center and number of rotations
 */
class Spiral : public StylableObject
{
    Coords center;
    int rotations;

public:
    /**
     * @brief Construct a new Spiral object with given parameters. Beware that
     * StylableObject::Style::width is especially important here, since that 'radius'
     * of the spiral is proportional to its width
     *
     * @throws std::invalid_argument If the number of rotations is 0 or less
     * @param style_ Optional width and color of the spiral
     * @param center_ Center of the spiral
     * @param rotations_ Number of rotations of the spiral
     */
    Spiral(const StylableObject::Style &style_, const Coords &center_, int rotations_);

    std::unique_ptr<Object> clone() const override;

    /**
     * @brief Render spiral with given offset and scale into image. Spiral is rendered
     * using quadratic Bezier curves, which form connected semi-circles with increasing
     * radii, creating a spiral
     *
     * @param image Image the spiral should be rendere into
     * @param offset Offset from the origin (0,0)
     * @param scale Scale of the spiral
     */
    void render(Image &image, const Coords &offset,
                const ScaleFactor &scale) const override;

    /**
     * @brief Parse spiral from given string
     *
     * @throws std::invalid_argument If the string couldn't be parsed
     * @param src String in the form "(100,100) rotations=5 width=2 color=#abcdef"
     * @return std::unique_ptr<Object>
     */
    static std::unique_ptr<Object> parse_from_str(const std::string &src);
};
