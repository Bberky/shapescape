/**
 * @file encoder.hpp
 * @author Adam Berkeš <berkeada@fit.cvut.cz>
 * @date 2023-05-06
 */

#pragma once

#include "../image/image.hpp"

#include <filesystem>
#include <memory>

/**
 * @brief Base class for any kind of encoder which
 * is capable of encoding images into desired format
 */
class Encoder
{
public:
    virtual ~Encoder();

    /**
     * @brief Main encoder method which encodes image into
     * the desired format and save it into file
     *
     * @param file File into which the encoded image should be save
     * @param image Image to be encoded
     */
    virtual void encode_to_file(const std::filesystem::path &file, const Image &image) const = 0;

    /**
     * @brief Clone the Encoder by creating a deep copy,
     * which is usually a cheap operation
     *
     * @return std::shared_ptr<Encoder>
     */
    virtual std::shared_ptr<Encoder> clone() const = 0;
};
