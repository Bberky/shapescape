/**
 * @file object.hpp
 * @author Adam Berkeš <berkeada@fit.cvut.cz>
 * @date 2023-05-06
 */

#pragma once

#include "../image/image.hpp"
#include "../vec2.hpp"

#include <memory>

/**
 * @brief Abstract class providing interface for any
 * kind of object which is renderable into an image,
 * generally a geometrical shape
 */
class Object
{
public:
    virtual ~Object();

    /**
     * @brief Clone the object by creating a deep copy
     *
     * @return std::unique_ptr<Object>
     */
    virtual std::unique_ptr<Object> clone() const = 0;

    /**
     * @brief Render object into image, given it's offset from
     * the origin (0,0), which represent the upper left corner
     * of the image and scale factor which enables two-dimensional
     * scaling and also reflections
     *
     * @param image Image into which the object should be rendered to
     * @param offset Offset from the origin
     * @param scale Scale of the object in either axis
     * and/or whether is should also be reflected (indicated by negative values)
     */
    virtual void render(Image &image, const Coords &offset, const ScaleFactor &scale) const = 0;

    /**
     * @brief Parse a new object from given string. This method
     * is deleted unless it is implemented by a specific Object.
     *
     * @param src Source string for the object to be parsed form
     * @return std::unique_ptr<Object>
     */
    static std::unique_ptr<Object> parse_from_str(const std::string &src) = delete;
};
