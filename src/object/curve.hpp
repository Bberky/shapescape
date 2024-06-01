/**
 * @file curve.hpp
 * @author Adam Berkeš <berkeada@fit.cvut.cz>
 * @date 2023-06-01
 */

#pragma once

#include "stylable_object.hpp"

#include <array>

/**
 * @brief Curve object representing quadratic Bézier curve
 * <a href="https://en.wikipedia.org/wiki/B%C3%A9zier_curve">Bézier curve</a>
 */
class Curve : public StylableObject
{
    /** Array of 3 control points P0 through P2 */
    std::array<Coords, 3> control_points;

public:
    /**
     * @brief Construct a new Curve object given its style and control points
     *
     * @param style_ Optional width and color of the curve
     * @param control_points_ Control point P0 through P2
     */
    Curve(const StylableObject::Style &style_, const std::array<Coords, 3> &control_points_);

    std::unique_ptr<Object> clone() const override;

    /**
     * @brief Render the curve into image with given offset and scale
     * using standard equation for quadratic Bézier curve:
     * B(t) = (1 - t)^2 * [(1 - t) * P0 + t * P1] + t * [(1 - t) * P1 + t * P2], t ∈ <0,1>
     *
     * @param image Image the curve should be rendered into
     * @param offset Offset from the origin (0,0)
     * @param scale Scale of the curve
     */
    void render(Image &image, const Coords &offset, const ScaleFactor &scale) const override;

    /**
     * @brief Parse the curve form given string
     *
     * @throws std::invalid_argument If the string couldn't be parsed
     * @param src String in the form "((100,100);(150,50);(200,100)) width=5 color=#edc"
     * @return std::unique_ptr<Object>
     */
    static std::unique_ptr<Object> parse_from_str(const std::string &src);
};
