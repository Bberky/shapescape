/**
 * @file image_builder.hpp
 * @author Adam Berkeš <berkeada@fit.cvut.cz>
 * @date 2023-05-06
 */

#pragma once

#include "pixel.hpp"

#include <vector>

/**
 * @brief General Image class representing an image
 * with constant dimensions and background which can
 * be exported to a file
 */
class Image
{
    /**
     * @brief Class represneting underlying image data,
     * which is a two-dimensional vector of pixels
     */
    class ImageBuffer
    {
        std::vector<std::vector<Pixel>> data;

    public:
        /**
         * @brief Construct a new Image Buffer object with specified
         * dimensions and background color
         *
         * @throws std::invalid_argument If either one of the dimensions
         * is negative
         * @param width
         * @param height
         * @param bg_color
         */
        ImageBuffer(int width, int height, const Pixel &bg_color);

        /**
         * @brief Try to set the pixel at the specified position
         *
         * @param x X-axis coordinate
         * @param y Y-axis coordinate
         * @param pixel
         * @return true If the position was valid, otherwise false
         */
        bool set_pixel(size_t x, size_t y, Pixel pixel);

        /**
         * @brief Get mutable reference to the pixel
         * specified by x and y coordinates
         *
         * @param x X-axis coordinate
         * @param y Y-axis coordinate
         * @return Pixel&
         */
        Pixel &operator()(size_t x, size_t y);

        /**
         * @brief Get pixel from the buffer specified
         * by x and y coordinates
         *
         * @param x X-axis coordinate
         * @param y Y-axis coordinate
         * @return Pixel
         */
        Pixel operator()(size_t x, size_t y) const;
    };

    ImageBuffer buffer;
    int width, height;

public:
    /**
     * @brief Construct a new Image object with specified
     * width, height and background color which defaults to
     * black if none is specified
     *
     * @throws std::invalid_argument If either one of the dimensions
     * entered is negative
     * @param width Width of the image
     * @param height Height of the image
     * @param bg_color Optional background color
     */
    Image(int width, int height, const Pixel &bg_color = Pixel());

    /** Width getter */
    int get_width() const;

    /** Height getter */
    int get_height() const;

    /** Calculate the raw size of the image in bytes */
    long get_size() const;

    /** Get mutable reference to the underlying data buffer */
    ImageBuffer &get_buffer();

    /** Get immutable reference to the underlying data buffer */
    const ImageBuffer &get_buffer() const;
};
