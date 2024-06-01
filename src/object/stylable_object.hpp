/**
 * @file stylable_object.hpp
 * @author Adam Berkeš <berkeada@fit.cvut.cz>
 * @date 2023-05-07
 */

#pragma once

#include "object.hpp"

/**
 * @brief Abstract class providing interface
 * for a subgroup of objects that are stylable,
 * meaning that they have configurable properties
 * which change the way they render
 */
class StylableObject : public Object
{
public:
    /**
     * @brief Container for general object styles:
     * width of the outline and color of the outline
     */
    struct Style
    {
        /** Width of the outline of the object */
        int width;
        /** Color of the outline of the object */
        Pixel color;

        /**
         * @brief Construct a new Style object with
         * the given values
         *
         * @param width_ Width of the outline
         * @param color_ Color of the outline
         */
        Style(int width_ = 1, Pixel color_ = {255, 255, 255});

        /**
         * @brief Construct a new Style object from source string
         * in the form "width=1 color=#fff", both "width" and "color"
         * are optional, if none of those are found, default values will be used
         *
         * @throws std::invalid_argument If the string couldn't be parsed,
         * or invalid style was entered
         * @param src String to parse into the style object
         */
        explicit Style(const std::string &src);
    };

    /** Style of the object */
    Style style;

    /**
     * @brief Construct a new Stylable Object object
     * with given style
     *
     * @param style_ Style of the object
     */
    StylableObject(const Style &style_ = {});
};
