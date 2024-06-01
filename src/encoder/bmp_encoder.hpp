/**
 * @file bpm_encoder.hpp
 * @author Adam Berkeš <berkeada@fit.cvut.cz>
 * @date 2023-05-06
 */

#pragma once

#include "encoder.hpp"

/**
 * @brief Encoder for encoding images into the BMP (bitmap) image format.
 * <a href="https://en.wikipedia.org/wiki/BMP_file_format">Format reference</a>
 */
class BMPEncoder : public Encoder
{
    /** File header size */
    static constexpr const int BMP_FILE_HEADER_SIZE = 14;
    /** Info header size */
    static constexpr const int BMP_INFO_HEADER_SIZE = 40;
    /** Basic structure of the file header */
    static constexpr const unsigned char BMP_FILE_HEADER[BMP_FILE_HEADER_SIZE] =
        {'B', 'M', 0, 0, 0, 0, 0, 0, 0, 0, BMP_FILE_HEADER_SIZE + BMP_INFO_HEADER_SIZE, 0, 0, 0};
    /** Basic structure of the info header */
    static constexpr const unsigned char BMP_INFO_HEADER[BMP_INFO_HEADER_SIZE] =
        {BMP_INFO_HEADER_SIZE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, sizeof(Pixel) * 8};

public:
    /**
     * @brief Encode image into BMP format, dynamically creating
     * neccessary headers and offsetting the image data
     *
     * @throws std::invalid_argument If the file couldn't be created or opened for writing
     * @throws std::runtime_exception If something went wrong with the file while writing into it
     * @param file File into which the image should be saved
     * @param image Image to be saved
     */
    void encode_to_file(const std::filesystem::path &file, const Image &image) const override;

    std::shared_ptr<Encoder> clone() const override;
};
