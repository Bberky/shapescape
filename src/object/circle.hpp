/**
 * @file elipse.hpp
 * @author Adam Berkeš <berkeada@fit.cvut.cz>
 * @date 2023-05-07
 */

#pragma once

#include "stylable_object.hpp"

/**
 * @brief Circle given by coordinates of its center and radius
 */
class Circle : public StylableObject
{
    Coords center;
    int radius;

    /**
     * @brief Plot eight symmetric octants of the circle into the image
     *
     * @param image Image where the octants should be drawn
     * @param c Center
     * @param d Displacement
     * @param x_shift X-axis shift
     * @param y_shit Y-axis shift
     */
    void draw_octants(Image &image, const Coords &c, const Coords &d,
                      int x_shift = 0, int y_shit = 0) const;

    /**
     * @brief Draw a circle using modified Bresenham's circle drawing algorithm
     *
     * @param image Image where the circle should be drawn
     * @param x0 X-coordinate of the center
     * @param y0 Y-coordinate of the center
     * @param r Radius
     */
    void draw_circle(Image &image, int x0, int y0, int r) const;

public:
    /**
     * @brief Construct a new Circle object with given parameters
     *
     * @param style_ Optional width and color of the circle
     * @param center_ Center of the circle
     * @param radius_ Radius of the circle
     */
    Circle(const StylableObject::Style &style_, Coords center_, int radius_);

    std::unique_ptr<Object> clone() const override;

    /**
     * @brief Render circle with given offset and scale into image
     * using modified Bresenham's circle drawing algorithm. Thicker circles are
     * rendered using concentric circles where the radii get incrementally smaller
     *
     * <a href="https://en.wikipedia.org/wiki/Midpoint_circle_algorithm">Alogrithm reference</a>
     * <a href="https://www.javatpoint.com/computer-graphics-bresenhams-circle-algorithm">Another reference</a>
     * @param image Image the circle should be rendered into
     * @param offset Offset from the origin (0,0)
     * @param scale Scale of the circle
     */
    void render(Image &image, const Coords &offset, const ScaleFactor &scale) const override;

    /**
     * @brief Parse circle from given string
     *
     * @throws std::invalid_argument If the string couldn't be parsed
     * @param src String in the form "(100,100) radius=50 width=5 color=#fff"
     * @return std::unique_ptr<Object>
     */
    static std::unique_ptr<Object> parse_from_str(const std::string &src);
};
