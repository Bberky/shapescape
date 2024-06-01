/**
 * @file elipse.hpp
 * @author Adam Berkeš <berkeada@fit.cvut.cz>
 * @date 2023-05-31
 */

#pragma once

#include "stylable_object.hpp"

/**
 * @brief Ellipse given by its center and two radii
 */
class Ellipse : public StylableObject
{
    Coords center;
    int radius_x, radius_y;

public:
    /**
     * @brief Construct a new Ellipse object with given parameters
     *
     * @param style_ Optional width and color of the ellipse
     * @param center_ Center of the ellipse
     * @param radius_x_ X-axis radius
     * @param radius_y_ Y-Axis radius
     */
    Ellipse(const StylableObject::Style &style_, const Coords &center_,
            int radius_x_, int radius_y_);

    std::unique_ptr<Object> clone() const override;

    /**
     * @brief Render ellipse using modified midpoint ellipse drawing algorithm. Thicker ellipses
     * are rendered using concentric ellipses where the radii get incrementally smaller
     *
     * <a href="https://en.wikipedia.org/wiki/Midpoint_circle_algorithm">Algorithm reference</a>
     * <a href="https://www.javatpoint.com/computer-graphics-midpoint-ellipse-algorithm">Another Reference</a>
     * @param image Image the ellipse should be rendered into
     * @param offset Offset from the origin (0,0)
     * @param scale Scale of the ellipse
     */
    void render(Image &image, const Coords &offset, const ScaleFactor &scale) const override;

    /**
     * @brief Parse the ellipse from given string
     *
     * @throws std::invalid_argument If the string couldn't be parsed
     * @param src String in the form "(100,100) radius_x=100 radius_y=50 width=3 color=#dddddd"
     * @return std::unique_ptr<Object>
     */
    static std::unique_ptr<Object> parse_from_str(const std::string &src);
};
