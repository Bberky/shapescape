/**
 * @file polygon.hpp
 * @author Adam Berkeš <berkeada@fit.cvut.cz>
 * @date 2023-06-01
 */

#pragma once

#include "stylable_object.hpp"

/**
 * @brief Polygon represented by a set of vertices, each consecutive pair
 * forms a line together with the first and last vertex
 */
class Polygon : public StylableObject
{
    std::vector<Coords> vertices;

    /**
     * @brief Check whether each 3 consecutive vertices are colinear
     *
     * @return true If the vertices are not colinear and therefore do
     * represent a legitimate polygon, otherwise false
     */
    bool check_polygon() const;

public:
    /**
     * @brief Construct a new Polygon object with given style and vertices.
     * Each consecutive pair of vertices (together with first and last vertex) form
     * a straight line which then form a polygon
     *
     * @throws std::invalid_argument If any 3 consecutive vertice of
     * the vertices given are colinear
     * @param style_ Optional width and color of the polygon
     * @param vertices_ Set of vertices which form the polygon
     */
    Polygon(const StylableObject::Style &style_, const std::vector<Coords> &vertices_);

    std::unique_ptr<Object> clone() const override;

    /**
     * @brief Render polygon with given offset and scale into image
     *
     * @param image Image the polygon should be rendered into
     * @param offset Offset of the polygon from origin (0,0)
     * @param scale Scale of the polygon
     */
    void render(Image &image, const Coords &offset, const ScaleFactor &scale) const override;

    /**
     * @brief Parse the polygon from given string
     *
     * @throws std::invalid_argument If the string couldn't be parsed
     * @param src String in the form "((100,100);(200,200);(100,300);(0,200)) width=2 color=#dcba98"
     * @return std::unique_ptr<Object>
     */
    static std::unique_ptr<Object> parse_from_str(const std::string &src);
};
