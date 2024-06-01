/**
 * @file png_encoder.hpp
 * @author Adam Berkeš <berkeada@fit.cvut.cz>
 * @date 2023-05-07
 */

#pragma once

#include "encoder.hpp"

/**
 * @brief Encoder for encoding images into the
 * PNG (Portable Network Graphics) image format, using libpng.
 * So far, this encoder can only handle 3 color channels,
 * meaning that it doesn't support the alpha channel and thus
 * doesn't supoprt transparency and opacity.
 * <a href="https://www.w3.org/TR/2003/REC-PNG-20031110/">Format reference</a>
 */
class PNGEncoder : public Encoder
{
public:
    /**
     * @brief Encode image into PNG format using libpng
     *
     * @throws std::invalid_argument If the file couldn't be created or opened for writing
     * @throws std::runtime_exception If something went wrong with the file while writing into it
     * @param file File into which the image should be saved
     * @param image Image to be saved
     */
    void encode_to_file(const std::filesystem::path &file, const Image &image) const override;

    std::shared_ptr<Encoder> clone() const override;
};
